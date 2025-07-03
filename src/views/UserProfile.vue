<template>
  <div class="profile-container">
    <div class="profile-box" v-if="!loading">
      <div class="avatar-container">
        <div class="avatar">
          {{ userInitials }}
        </div>
      </div>
      <div class="user-info">
        <h2>{{ userStore.user?.username }}</h2>
        <p class="email">{{ userStore.user?.email }}</p>
        <div class="account-info">
          <div class="info-item">
            <span class="label">账户余额</span>
            <span class="value">¥{{ userStore.user?.balance }}</span>
          </div>
          <div class="info-item">
            <span class="label">账户状态</span>
            <span
              :class="[
                'status',
                userStore.user?.isActive ? 'active' : 'inactive',
              ]"
            >
              {{ userStore.user?.isActive ? "正常" : "已冻结" }}
            </span>
          </div>
        </div>
      </div>
      <div class="stats">
        <div class="stat-item">
          <span class="stat-value">{{ transactionCount }}</span>
          <span class="stat-label">交易次数</span>
        </div>
        <div class="stat-item">
          <span class="stat-value">{{ spendingAmount }}</span>
          <span class="stat-label">总消费</span>
        </div>
      </div>

      <!-- 交易记录部分 -->
      <div class="transactions-section">
        <h3>交易记录</h3>
        <div
          class="chart-container"
          v-if="userStore.user?.transactions?.length"
        >
          <Bar :data="chartData" :options="chartOptions" />
        </div>
        <div
          class="transactions-list"
          v-if="userStore.user?.transactions?.length"
        >
          <table>
            <thead>
              <tr>
                <th>日期</th>
                <th>类型</th>
                <th>金额</th>
                <th>描述</th>
              </tr>
            </thead>
            <tbody>
              <tr
                v-for="transaction in userStore.user?.transactions"
                :key="transaction.id"
              >
                <td>{{ transaction.date }}</td>
                <td>{{ transaction.type }}</td>
                <td :class="transaction.amount > 0 ? 'positive' : 'negative'">
                  {{ transaction.amount > 0 ? "+" : ""
                  }}{{ transaction.amount }}
                </td>
                <td>{{ transaction.description }}</td>
              </tr>
            </tbody>
          </table>
        </div>
        <div class="empty-state" v-else>
          <p>暂无交易记录</p>
        </div>
      </div>
    </div>
    <div class="loading-container" v-else>
      <div class="loading-spinner"></div>
      <p>加载用户信息中...</p>
    </div>
  </div>
</template>

<script setup>
import { computed, ref, onMounted } from "vue";
import { useUserStore } from "../stores/user";
import { userApi } from "../api/user";
import { Bar } from "vue-chartjs";
import {
  Chart as ChartJS,
  Title,
  Tooltip,
  Legend,
  BarElement,
  CategoryScale,
  LinearScale,
} from "chart.js";

ChartJS.register(
  Title,
  Tooltip,
  Legend,
  BarElement,
  CategoryScale,
  LinearScale
);

const userStore = useUserStore();
const loading = ref(true);

// 在组件挂载时获取用户信息
onMounted(async () => {
  try {
    const token = localStorage.getItem("token");
    if (token) {
      console.log("找到token，获取用户信息");
      await fetchUserProfile();
    } else {
      console.error("未找到token，无法获取用户信息");
    }
  } finally {
    loading.value = false;
  }
});

// 获取用户资料信息
const fetchUserProfile = async () => {
  try {
    const response = await userApi.getProfile();
    console.log("获取到的用户资料:", response.data);

    if (response.data && response.data.user) {
      userStore.setUser(response.data.user);
      userStore.setIsLoggedIn(true);
    }
  } catch (error) {
    console.error("获取用户资料失败:", error);
    alert("获取用户信息失败，请重新登录");
  }
};

const userInitials = computed(() => {
  const username = userStore.user?.username || "";
  return username.charAt(0).toUpperCase();
});

const transactionCount = computed(() => {
  return userStore.user?.transactions?.length || 0;
});

const spendingAmount = computed(() => {
  if (!userStore.user?.transactions) return 0;

  const spentAmount = userStore.user.transactions
    .filter((t) => t.amount < 0)
    .reduce((total, t) => total + Math.abs(t.amount), 0);

  return spentAmount;
});

const chartData = computed(() => {
  if (!userStore.user?.transactions?.length) return null;

  const transactions = userStore.user.transactions;
  const dates = transactions.map((t) => t.date);
  const amounts = transactions.map((t) => t.amount);

  return {
    labels: dates,
    datasets: [
      {
        label: "交易金额",
        data: amounts,
        backgroundColor: amounts.map((amount) =>
          amount > 0 ? "#4CAF50" : "#ff4d4f"
        ),
        borderColor: amounts.map((amount) =>
          amount > 0 ? "#388e3c" : "#ff4d4f"
        ),
        borderWidth: 1,
      },
    ],
  };
});

const chartOptions = {
  responsive: true,
  maintainAspectRatio: false,
  scales: {
    y: {
      beginAtZero: true,
    },
  },
};
</script>

<style scoped>
.profile-container {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background-color: #f5f5f5;
  padding: 2rem;
}

.profile-box {
  background: white;
  padding: 2rem;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  width: 100%;
  max-width: 800px;
  text-align: center;
}

.avatar-container {
  margin-bottom: 1.5rem;
}

.avatar {
  width: 120px;
  height: 120px;
  border-radius: 50%;
  background-color: #4caf50;
  color: white;
  display: flex;
  align-items: center;
  justify-content: center;
  font-size: 3rem;
  margin: 0 auto;
  font-weight: bold;
}

.user-info {
  margin-bottom: 2rem;
}

.user-info h2 {
  font-size: 2rem;
  color: #333;
  margin-bottom: 0.5rem;
}

.email {
  color: #666;
  font-size: 1.1rem;
  margin-bottom: 1rem;
}

.account-info {
  display: flex;
  flex-direction: column;
  gap: 1rem;
  margin-top: 1rem;
  padding: 1rem;
  background-color: #f8f9fa;
  border-radius: 8px;
}

.info-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
}

.label {
  color: #666;
  font-size: 1rem;
}

.value {
  color: #333;
  font-size: 1.2rem;
  font-weight: bold;
}

.status {
  padding: 0.25rem 0.5rem;
  border-radius: 4px;
  font-size: 0.9rem;
  font-weight: bold;
}

.status.active {
  background-color: #4caf50;
  color: white;
}

.status.inactive {
  background-color: #ff4d4f;
  color: white;
}

.stats {
  display: flex;
  justify-content: center;
  gap: 2rem;
  margin-top: 2rem;
  padding-top: 2rem;
  border-top: 1px solid #eee;
}

.stat-item {
  display: flex;
  flex-direction: column;
  align-items: center;
}

.stat-value {
  font-size: 1.5rem;
  font-weight: bold;
  color: #333;
}

.stat-label {
  color: #666;
  font-size: 0.9rem;
}

/* 交易记录样式 */
.transactions-section {
  margin-top: 2rem;
  padding-top: 2rem;
  border-top: 1px solid #eee;
  text-align: left;
}

.transactions-section h3 {
  margin-bottom: 1.5rem;
  text-align: center;
  color: #333;
}

.chart-container {
  height: 250px;
  margin-bottom: 2rem;
}

.transactions-list {
  width: 100%;
  overflow-x: auto;
}

.transactions-list table {
  width: 100%;
  border-collapse: collapse;
}

.transactions-list th,
.transactions-list td {
  padding: 0.75rem;
  text-align: left;
  border-bottom: 1px solid #eee;
}

.transactions-list th {
  background-color: #f8f9fa;
  font-weight: bold;
  color: #333;
}

.positive {
  color: #4caf50;
}

.negative {
  color: #ff4d4f;
}

.empty-state {
  text-align: center;
  padding: 2rem;
  color: #666;
}

/* 添加加载状态样式 */
.loading-container {
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: center;
  min-height: 400px;
  text-align: center;
}

.loading-spinner {
  width: 50px;
  height: 50px;
  border: 5px solid #f3f3f3;
  border-top: 5px solid #4caf50;
  border-radius: 50%;
  animation: spin 1s linear infinite;
  margin-bottom: 20px;
}

@keyframes spin {
  0% {
    transform: rotate(0deg);
  }
  100% {
    transform: rotate(360deg);
  }
}
</style>
