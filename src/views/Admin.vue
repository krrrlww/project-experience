<script setup>
import { ref, onMounted } from 'vue';
import { useRouter } from 'vue-router';
import * as echarts from 'echarts';

const router = useRouter();
const searchQuery = ref('');
const users = ref([
  {
    id: 1,
    username: '张三',
    email: 'zhangsan@example.com',
    balance: 1000,
    status: '正常',
    phone: '13800138001',
    records: [
      { type: '充值', amount: 500, date: '2024-03-01' },
      { type: '消费', amount: -200, date: '2024-03-05' },
      { type: '充值', amount: 1000, date: '2024-03-10' },
      { type: '消费', amount: -300, date: '2024-03-15' },
      { type: '充值', amount: 800, date: '2024-03-20' },
      { type: '消费', amount: -400, date: '2024-03-25' }
    ]
  },
  {
    id: 2,
    username: '李四',
    email: 'lisi@example.com',
    balance: 2000,
    status: '正常',
    phone: '13800138002',
    records: [
      { type: '充值', amount: 1000, date: '2024-03-02' },
      { type: '消费', amount: -500, date: '2024-03-08' },
      { type: '充值', amount: 2000, date: '2024-03-12' },
      { type: '消费', amount: -800, date: '2024-03-18' },
      { type: '充值', amount: 1500, date: '2024-03-22' },
      { type: '消费', amount: -600, date: '2024-03-28' }
    ]
  },
  {
    "id": 3,
    "username": "Michael Brown",
    "email": "michael.brown@hotmail.com",
    "balance": 500,
    "status": "冻结",
    "phone": "13800138003"
  },
  {
    "id": 4,
    "username": "Emily Davis",
    "email": "emily.davis@outlook.com",
    "balance": 3000,
    "status": "正常",
    "phone": "13800138004"
  },
  {
    "id": 5,
    "username": "David Wilson",
    "email": "david.wilson@aol.com",
    "balance": 1500,
    "status": "正常",
    "phone": "13800138005"
  },
  {
    "id": 6,
    "username": "Sarah Johnson",
    "email": "sarah.johnson@icloud.com",
    "balance": 800,
    "status": "冻结",
    "phone": "13800138006"
  },
  {
    "id": 7,
    "username": "Robert Lee",
    "email": "robert.lee@protonmail.com",
    "balance": 2500,
    "status": "正常",
    "phone": "13800138007"
  },
  {
    "id": 8,
    "username": "Laura White",
    "email": "laura.white@zoho.com",
    "balance": 1200,
    "status": "正常",
    "phone": "13800138008"
  },
  {
    "id": 9,
    "username": "James Hall",
    "email": "james.hall@yandex.com",
    "balance": 1800,
    "status": "冻结",
    "phone": "13800138009"
  },
  {
    "id": 10,
    "username": "Olivia Clark",
    "email": "olivia.clark@tutanota.com",
    "balance": 900,
    "status": "正常",
    "phone": "13800138010"
  }
]);

const filteredUsers = ref([...users.value]);
const showUserDetail = ref(false);
const currentUser = ref(null);
const chartInstance = ref(null);

// 搜索功能
const handleSearch = () => {
  const query = searchQuery.value.toLowerCase();
  filteredUsers.value = users.value.filter(user => 
    user.username.toLowerCase().includes(query) ||
    user.email.toLowerCase().includes(query) ||
    user.phone.includes(query)
  );
};

// 冻结用户
const freezeUser = (userId) => {
  const user = users.value.find(u => u.id === userId);
  if (user) {
    user.status = user.status === '正常' ? '冻结' : '正常';
    handleSearch(); // 更新过滤后的列表
  }
};

// 删除用户
const deleteUser = (userId) => {
  if (confirm('确定要删除该用户吗？此操作不可恢复！')) {
    users.value = users.value.filter(u => u.id !== userId);
    handleSearch(); // 更新过滤后的列表
  }
};

// 显示用户详情
const showUserDetails = (user) => {
  currentUser.value = user;
  showUserDetail.value = true;
  
  // 在下一个 tick 初始化图表，确保 DOM 已经渲染
  setTimeout(() => {
    initChart();
  }, 0);
};

// 初始化图表
const initChart = () => {
  if (!currentUser.value) return;
  
  const chartDom = document.getElementById('userChart');
  if (!chartDom) return;
  
  // 如果已经有图表实例，先销毁
  if (chartInstance.value) {
    chartInstance.value.dispose();
  }
  
  // 创建新的图表实例
  chartInstance.value = echarts.init(chartDom);
  
  // 准备数据
  const dates = currentUser.value.records.map(r => r.date);
  const amounts = currentUser.value.records.map(r => r.amount);
  
  // 配置图表选项
  const option = {
    title: {
      text: '充值消费记录',
      left: 'center'
    },
    tooltip: {
      trigger: 'axis',
      formatter: function(params) {
        const data = params[0];
        return `${data.name}<br/>${data.value > 0 ? '充值' : '消费'}: ${Math.abs(data.value)}元`;
      }
    },
    xAxis: {
      type: 'category',
      data: dates,
      axisLabel: {
        rotate: 45
      }
    },
    yAxis: {
      type: 'value',
      name: '金额 (元)'
    },
    series: [
      {
        name: '金额',
        type: 'bar',
        data: amounts,
        itemStyle: {
          color: function(params) {
            return params.value > 0 ? '#67C23A' : '#F56C6C';
          }
        },
        label: {
          show: true,
          position: 'top',
          formatter: function(params) {
            return params.value > 0 ? `+${params.value}` : params.value;
          }
        }
      }
    ]
  };
  
  // 设置图表选项
  chartInstance.value.setOption(option);
};

// 关闭用户详情
const closeUserDetail = () => {
  showUserDetail.value = false;
  currentUser.value = null;
  if (chartInstance.value) {
    chartInstance.value.dispose();
    chartInstance.value = null;
  }
};

// 检查管理员权限
onMounted(() => {
  // 移除权限检查，因为登录时已经验证过了
});


import { useCounterStore } from '@/stores/counter';
const store = useCounterStore();

const jump=()=>{
  store.isAdmin = false;
  router.push('/');
}
</script>

<template>
  <div class="admin-page">
    <!-- 添加顶部栏 -->
    <div class="admin-header">
      <div class="header-left">
        <button class="back-btn" @click="jump">
          <svg xmlns="http://www.w3.org/2000/svg" width="24" height="24" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
            <path d="M19 12H5M12 19l-7-7 7-7"/>
          </svg>
          返回首页
        </button>
      </div>
      <div class="header-right">
        <div class="admin-profile">
          <img src="https://api.dicebear.com/7.x/avataaars/svg?seed=admin" alt="管理员头像" class="admin-avatar" />
          <span class="admin-name">管理员</span>
        </div>
      </div>
    </div>

    <div class="admin-container">
      <div class="admin-header">
        <h1>用户管理</h1>
        <div class="search-box">
          <input
            type="text"
            v-model="searchQuery"
            @input="handleSearch"
            placeholder="搜索用户名、邮箱或手机号..."
            class="search-input"
          />
          <button class="search-btn" @click="handleSearch">
            <svg xmlns="http://www.w3.org/2000/svg" width="20" height="20" viewBox="0 0 24 24" fill="none" stroke="currentColor" stroke-width="2" stroke-linecap="round" stroke-linejoin="round">
              <circle cx="11" cy="11" r="8"></circle>
              <line x1="21" y1="21" x2="16.65" y2="16.65"></line>
            </svg>
          </button>
        </div>
      </div>

      <div class="table-container">
        <table class="admin-table">
          <thead>
            <tr>
              <th>用户名</th>
              <th>邮箱</th>
              <th>手机号</th>
              <th>余额</th>
              <th>状态</th>
              <th>操作</th>
            </tr>
          </thead>
          <tbody>
            <tr v-for="user in filteredUsers" :key="user.id">
              <td>{{ user.username }}</td>
              <td>{{ user.email }}</td>
              <td>{{ user.phone }}</td>
              <td>¥{{ user.balance.toFixed(2) }}</td>
              <td>
                <span :class="['status-badge', user.status === '正常' ? 'status-normal' : 'status-frozen']">
                  {{ user.status }}
                </span>
              </td>
              <td class="actions">
                <button 
                  class="action-btn detail-btn"
                  @click="showUserDetails(user)"
                >
                  详情
                </button>
                <button 
                  class="action-btn freeze-btn"
                  @click="freezeUser(user.id)"
                  :class="{ 'frozen': user.status === '冻结' }"
                >
                  {{ user.status === '正常' ? '冻结' : '解冻' }}
                </button>
                <button 
                  class="action-btn delete-btn"
                  @click="deleteUser(user.id)"
                >
                  删除
                </button>
              </td>
            </tr>
          </tbody>
        </table>
      </div>
    </div>

    <!-- 用户详情弹窗 -->
    <div class="user-detail-modal" v-if="showUserDetail">
      <div class="modal-content">
        <div class="modal-header">
          <h2>{{ currentUser?.username }} 的用户详情</h2>
          <button class="close-btn" @click="closeUserDetail">×</button>
        </div>
        <div class="modal-body">
          <div class="user-info">
            <div class="info-item">
              <span class="info-label">用户名:</span>
              <span class="info-value">{{ currentUser?.username }}</span>
            </div>
            <div class="info-item">
              <span class="info-label">邮箱:</span>
              <span class="info-value">{{ currentUser?.email }}</span>
            </div>
            <div class="info-item">
              <span class="info-label">手机号:</span>
              <span class="info-value">{{ currentUser?.phone }}</span>
            </div>
            <div class="info-item">
              <span class="info-label">当前余额:</span>
              <span class="info-value">¥{{ currentUser?.balance.toFixed(2) }}</span>
            </div>
            <div class="info-item">
              <span class="info-label">账户状态:</span>
              <span class="info-value" :class="currentUser?.status === '正常' ? 'status-normal' : 'status-frozen'">
                {{ currentUser?.status }}
              </span>
            </div>
          </div>
          
          <div class="chart-container">
            <div id="userChart" style="width: 100%; height: 400px;"></div>
          </div>
          
          <div class="records-table">
            <h3>交易记录</h3>
            <table>
              <thead>
                <tr>
                  <th>日期</th>
                  <th>类型</th>
                  <th>金额</th>
                </tr>
              </thead>
              <tbody>
                <tr v-for="(record, index) in currentUser?.records" :key="index">
                  <td>{{ record.date }}</td>
                  <td :class="record.type === '充值' ? 'recharge' : 'consume'">
                    {{ record.type }}
                  </td>
                  <td :class="record.amount > 0 ? 'recharge' : 'consume'">
                    {{ record.amount > 0 ? '+' : '' }}{{ record.amount }}
                  </td>
                </tr>
              </tbody>
            </table>
          </div>
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.admin-page {
  min-height: 100vh;
  background-color: #f8f9fa;
}

.admin-header {
  background-color: white;
  padding: 1rem 2rem;
  display: flex;
  justify-content: space-between;
  align-items: center;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  position: sticky;
  top: 0;
  z-index: 1000;
}

.header-left {
  display: flex;
  align-items: center;
}

.back-btn {
  display: flex;
  align-items: center;
  gap: 0.5rem;
  padding: 0.5rem 1rem;
  border: none;
  background-color: transparent;
  color: #333;
  font-size: 1rem;
  cursor: pointer;
  transition: all 0.3s;
  border-radius: 6px;
}

.back-btn:hover {
  background-color: #f8f9fa;
  color: #ff6b35;
}

.back-btn svg {
  width: 20px;
  height: 20px;
}

.header-right {
  display: flex;
  align-items: center;
}

.admin-profile {
  display: flex;
  align-items: center;
  gap: 1rem;
  padding: 0.5rem 1rem;
  background-color: #f8f9fa;
  border-radius: 8px;
  transition: all 0.3s;
}

.admin-profile:hover {
  background-color: #f0f0f0;
}

.admin-avatar {
  width: 40px;
  height: 40px;
  border-radius: 50%;
  border: 2px solid #ff6b35;
}

.admin-name {
  font-weight: 500;
  color: #333;
}

.admin-container {
  max-width: 1200px;
  margin: 2rem auto;
  padding: 0 1rem;
}

.admin-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  margin-bottom: 2rem;
}

.admin-header h1 {
  color: #333;
  font-size: 1.8rem;
  margin: 0;
}

.search-box {
  display: flex;
  align-items: center;
  background: white;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
  overflow: hidden;
  width: 400px;
}

.search-input {
  flex: 1;
  padding: 0.8rem 1rem;
  border: none;
  outline: none;
  font-size: 1rem;
  color: #333;
}

.search-btn {
  background: #ff6b35;
  border: none;
  padding: 0.8rem;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  color: white;
  transition: background-color 0.3s;
}

.search-btn:hover {
  background: #e85a2a;
}

.table-container {
  background: white;
  border-radius: 12px;
  box-shadow: 0 4px 12px rgba(0, 0, 0, 0.1);
  overflow: hidden;
}

.admin-table {
  width: 100%;
  border-collapse: collapse;
}

.admin-table th,
.admin-table td {
  padding: 1rem;
  text-align: left;
  border-bottom: 1px solid #eee;
}

.admin-table th {
  background: #f8f9fa;
  font-weight: 600;
  color: #333;
}

.admin-table tr:hover {
  background: #f8f9fa;
}

.status-badge {
  padding: 0.4rem 0.8rem;
  border-radius: 20px;
  font-size: 0.9rem;
  font-weight: 500;
}

.status-normal {
  background: #e6f4ea;
  color: #1e7e34;
}

.status-frozen {
  background: #fde8e8;
  color: #dc3545;
}

.actions {
  display: flex;
  gap: 0.5rem;
}

.action-btn {
  padding: 0.5rem 1rem;
  border: none;
  border-radius: 6px;
  font-size: 0.9rem;
  font-weight: 500;
  cursor: pointer;
  transition: all 0.3s;
}

.detail-btn {
  background-color: #409eff;
  color: white;
}

.detail-btn:hover {
  background-color: #3a8ee6;
}

.freeze-btn {
  background: #e3f2fd;
  color: #1976d2;
}

.freeze-btn.frozen {
  background: #fde8e8;
  color: #dc3545;
}

.delete-btn {
  background: #fde8e8;
  color: #dc3545;
}

.action-btn:hover {
  transform: translateY(-1px);
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
}

@media (max-width: 768px) {
  .admin-header {
    flex-direction: column;
    gap: 1rem;
  }

  .search-box {
    width: 100%;
  }

  .table-container {
    overflow-x: auto;
  }

  .admin-table {
    min-width: 800px;
  }
}

/* 用户详情弹窗样式 */
.user-detail-modal {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 2000;
}

.modal-content {
  background-color: white;
  border-radius: 12px;
  width: 80%;
  max-width: 900px;
  max-height: 90vh;
  overflow-y: auto;
  box-shadow: 0 4px 20px rgba(0, 0, 0, 0.15);
}

.modal-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 1.5rem;
  border-bottom: 1px solid #eee;
}

.modal-header h2 {
  margin: 0;
  color: #333;
  font-size: 1.5rem;
}

.close-btn {
  background: none;
  border: none;
  font-size: 1.5rem;
  cursor: pointer;
  color: #999;
  transition: color 0.3s;
}

.close-btn:hover {
  color: #333;
}

.modal-body {
  padding: 1.5rem;
}

.user-info {
  display: grid;
  grid-template-columns: repeat(2, 1fr);
  gap: 1rem;
  margin-bottom: 2rem;
  padding: 1rem;
  background-color: #f8f9fa;
  border-radius: 8px;
}

.info-item {
  display: flex;
  flex-direction: column;
}

.info-label {
  font-size: 0.875rem;
  color: #666;
  margin-bottom: 0.25rem;
}

.info-value {
  font-size: 1rem;
  color: #333;
  font-weight: 500;
}

.chart-container {
  margin: 2rem 0;
  padding: 1rem;
  background-color: white;
  border-radius: 8px;
  box-shadow: 0 2px 8px rgba(0, 0, 0, 0.1);
}

.records-table {
  margin-top: 2rem;
}

.records-table h3 {
  margin-bottom: 1rem;
  color: #333;
}

.records-table table {
  width: 100%;
  border-collapse: collapse;
}

.records-table th,
.records-table td {
  padding: 0.75rem;
  text-align: left;
  border-bottom: 1px solid #eee;
}

.records-table th {
  background-color: #f8f9fa;
  font-weight: 600;
  color: #333;
}

.recharge {
  color: #67c23a;
  font-weight: 500;
}

.consume {
  color: #f56c6c;
  font-weight: 500;
}
</style> 