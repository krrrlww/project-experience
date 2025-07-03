<template>
  <div class="admin-container">
    <div class="admin-box">
      <h2>管理员仪表盘</h2>
      <div class="user-list">
        <h3>用户列表</h3>
        <div class="search-bar">
          <input
            type="text"
            v-model="searchQuery"
            placeholder="搜索用户..."
            class="search-input"
          />
        </div>
        <div class="table-container">
          <table>
            <thead>
              <tr>
                <th>ID</th>
                <th>用户名</th>
                <th>邮箱</th>
                <th>余额</th>
                <th>状态</th>
                <th>操作</th>
              </tr>
            </thead>
            <tbody>
              <tr v-for="user in filteredUsers" :key="user.id">
                <td>{{ user.id }}</td>
                <td>{{ user.username }}</td>
                <td>{{ user.email }}</td>
                <td>¥{{ user.balance }}</td>
                <td>
                  <span
                    :class="[
                      'status-badge',
                      user.isActive ? 'active' : 'inactive',
                    ]"
                  >
                    {{ user.isActive ? "正常" : "已冻结" }}
                  </span>
                </td>
                <td>
                  <div class="action-buttons">
                    <button
                      class="action-button freeze"
                      @click="handleToggleUserStatus(user.id)"
                      :disabled="user.isAdmin"
                    >
                      {{ user.isActive ? "冻结" : "解冻" }}
                    </button>
                    <button
                      class="action-button delete"
                      @click="handleDeleteUser(user.id)"
                      :disabled="user.isAdmin"
                    >
                      删除
                    </button>
                    <button
                      class="action-button details"
                      @click="showUserDetails(user)"
                    >
                      详情
                    </button>
                  </div>
                </td>
              </tr>
            </tbody>
          </table>
        </div>
      </div>
    </div>

    <!-- 用户详情弹窗 -->
    <div v-if="selectedUser" class="modal-overlay" @click="closeModal">
      <div class="modal-content" @click.stop>
        <div class="modal-header">
          <h3>{{ selectedUser.username }} 的消费记录</h3>
          <button class="close-button" @click="closeModal">×</button>
        </div>
        <div class="modal-body">
          <div class="chart-container">
            <Bar :data="chartData" :options="chartOptions" />
          </div>
          <div class="transactions-list">
            <h4>交易记录</h4>
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
                  v-for="transaction in selectedUser.transactions"
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
        </div>
      </div>
    </div>
  </div>
</template>

<script setup>
import { ref, computed } from "vue";
import { useUserStore } from "../stores/user";
import usersData from "../data/users.json";
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
const searchQuery = ref("");
const selectedUser = ref(null);

// 确保只有管理员可以访问此页面
if (!userStore.user?.isAdmin) {
  window.location.href = "/";
}

const filteredUsers = computed(() => {
  return usersData.users.filter((user) => {
    const query = searchQuery.value.toLowerCase();
    return (
      user.username.toLowerCase().includes(query) ||
      user.email.toLowerCase().includes(query)
    );
  });
});

const chartData = computed(() => {
  if (!selectedUser.value) return null;

  const transactions = selectedUser.value.transactions;
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

const showUserDetails = (user) => {
  selectedUser.value = user;
};

const closeModal = () => {
  selectedUser.value = null;
};

const handleToggleUserStatus = (userId) => {
  const user = usersData.users.find((u) => u.id === userId);
  if (user) {
    user.isActive = !user.isActive;
  }
};

const handleDeleteUser = (userId) => {
  if (confirm("确定要删除此用户吗？")) {
    const index = usersData.users.findIndex((user) => user.id === userId);
    if (index !== -1) {
      usersData.users.splice(index, 1);
    }
  }
};
</script>

<style scoped>
.admin-container {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background-color: #f5f5f5;
  padding: 2rem;
}

.admin-box {
  background: white;
  padding: 2rem;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  width: 100%;
  max-width: 1000px;
}

h2 {
  text-align: center;
  margin-bottom: 2rem;
  color: #333;
}

h3 {
  margin-bottom: 1rem;
  color: #333;
}

.search-bar {
  margin-bottom: 1rem;
}

.search-input {
  width: 100%;
  padding: 0.75rem;
  border: 1px solid #ddd;
  border-radius: 4px;
  font-size: 1rem;
}

.table-container {
  overflow-x: auto;
}

table {
  width: 100%;
  border-collapse: collapse;
  margin-top: 1rem;
}

th,
td {
  padding: 1rem;
  text-align: left;
  border-bottom: 1px solid #eee;
  color: #333;
}

th {
  background-color: #f8f9fa;
  font-weight: bold;
  color: #333;
}

.action-buttons {
  display: flex;
  gap: 0.5rem;
}

.action-button {
  padding: 0.5rem 1rem;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  font-size: 0.9rem;
  transition: all 0.3s ease;
}

.freeze {
  background-color: #faad14;
  color: white;
}

.freeze:hover {
  background-color: #ffc53d;
}

.delete {
  background-color: #ff4d4f;
  color: white;
}

.delete:hover {
  background-color: #ff7875;
}

.details {
  background-color: #4caf50;
  color: white;
}

.details:hover {
  background-color: #388e3c;
}

.delete:disabled,
.freeze:disabled {
  background-color: #ccc;
  cursor: not-allowed;
}

.status-badge {
  padding: 0.25rem 0.5rem;
  border-radius: 4px;
  font-size: 0.8rem;
  font-weight: bold;
}

.status-badge.active {
  background-color: #4caf50;
  color: white;
}

.status-badge.inactive {
  background-color: #ff4d4f;
  color: white;
}

/* 弹窗样式 */
.modal-overlay {
  position: fixed;
  top: 0;
  left: 0;
  right: 0;
  bottom: 0;
  background-color: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 1000;
}

.modal-content {
  background: white;
  padding: 2rem;
  border-radius: 8px;
  width: 90%;
  max-width: 800px;
  max-height: 90vh;
  overflow-y: auto;
}

.modal-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 1.5rem;
}

.close-button {
  background: none;
  border: none;
  font-size: 1.5rem;
  cursor: pointer;
  color: #666;
}

.chart-container {
  height: 300px;
  margin-bottom: 2rem;
}

.transactions-list {
  margin-top: 2rem;
}

.transactions-list table {
  width: 100%;
}

.transactions-list th,
.transactions-list td {
  padding: 0.75rem;
}

.positive {
  color: #4caf50;
}

.negative {
  color: #ff4d4f;
}
</style>
