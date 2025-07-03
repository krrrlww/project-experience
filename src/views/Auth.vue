<script setup>
import { ref } from 'vue';
import { useRouter } from 'vue-router';
import { updateCurrentUser } from '@/utils/eventBus';
import { useCounterStore } from '@/stores/counter';

const store = useCounterStore();

const router = useRouter();
const isLogin = ref(true);
const username = ref('');
const password = ref('');
const confirmPassword = ref('');
const email = ref('');
const phone = ref('');
const avatar = ref('https://api.dicebear.com/7.x/avataaars/svg?seed=' + Math.random());
const error = ref('');
const success = ref('');

const toggleMode = () => {
  isLogin.value = !isLogin.value;
  error.value = '';
};

const handleSubmit = async (event) => {
  // 阻止表单默认提交行为
  event.preventDefault();
  
  try {
    if (isLogin.value) {
      // 登录逻辑
      if(username.value == 'admin' && password.value == '123'){
        store.isAdmin = true;
        router.push('/admin');
        return
      }
      const users = JSON.parse(localStorage.getItem('users') || '[]');
      const user = users.find(u => u.username === username.value && u.password === password.value);
     if (user) {
        localStorage.setItem('currentUser', JSON.stringify(user));
        updateCurrentUser(user); // 更新全局用户状态
        router.push('/');
      } else {
        alert('用户名或密码错误');
      }
    } else {
      // 注册逻辑
      if (password.value !== confirmPassword.value) {
        alert('两次输入的密码不一致');
        return;
      }
      
      const users = JSON.parse(localStorage.getItem('users') || '[]');
      
      // 检查用户名是否已存在
      if (users.some(u => u.username === username.value)) {
        alert('用户名已存在');
        return;
      }
      
      // 创建新用户
      const newUser = {
        id: Date.now(),
        username: username.value,
        password: password.value,
        email: email.value,
        phone: phone.value,
        avatar: avatar.value
      };
      
      // 添加到用户列表
      users.push(newUser);
      localStorage.setItem('users', JSON.stringify(users));
      
      // 自动登录
      localStorage.setItem('currentUser', JSON.stringify(newUser));
      updateCurrentUser(newUser); // 更新全局用户状态
      router.push('/');
    }
  } catch (error) {
    console.error('操作失败:', error);
    alert('操作失败，请重试');
  }
};
</script>

<template>
  <div class="auth-container">
    <div class="auth-box">
      <h2>{{ isLogin ? '登录' : '注册' }}</h2>
      <form @submit="handleSubmit" class="auth-form">
        <div class="form-group">
          <label for="username">用户名</label>
          <input
            type="text"
            id="username"
            v-model="username"
            placeholder="请输入用户名"
            required
          />
        </div>
        <div class="form-group">
          <label for="password">密码</label>
          <input
            type="password"
            id="password"
            v-model="password"
            placeholder="请输入密码"
            required
          />
        </div>
        <template v-if="!isLogin">
          <div class="form-group">
            <label for="confirmPassword">确认密码</label>
            <input
              type="password"
              id="confirmPassword"
              v-model="confirmPassword"
              placeholder="请再次输入密码"
              required
            />
          </div>
          <div class="form-group">
            <label for="email">邮箱</label>
            <input
              type="email"
              id="email"
              v-model="email"
              placeholder="请输入邮箱"
              required
            />
          </div>
          <div class="form-group">
            <label for="phone">电话</label>
            <input
              type="tel"
              id="phone"
              v-model="phone"
              placeholder="请输入电话"
              required
            />
          </div>
        </template>
        <div class="error-message" v-if="error">{{ error }}</div>
        <div class="success-message" v-if="success">{{ success }}</div>
        <button type="submit" class="submit-btn">
          {{ isLogin ? '登录' : '注册' }}
        </button>
        <p class="toggle-text">
          {{ isLogin ? '还没有账号？' : '已有账号？' }}
          <a href="#" @click.prevent="toggleMode">
            {{ isLogin ? '立即注册' : '立即登录' }}
          </a>
        </p>
      </form>
    </div>
  </div>
</template>

<style scoped>
.auth-container {
  min-height: calc(100vh - 72px);
  display: flex;
  justify-content: center;
  align-items: center;
  background-color: #f8f9fa;
  padding: 2rem;
}

.auth-box {
  background: white;
  padding: 2rem;
  border-radius: 8px;
  box-shadow: 0 4px 6px rgba(0, 0, 0, 0.1);
  width: 100%;
  max-width: 400px;
}

h2 {
  text-align: center;
  color: #333;
  margin-bottom: 2rem;
}

.auth-form {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
}

.form-group {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
}

label {
  color: #555;
  font-weight: 500;
}

input {
  padding: 0.8rem;
  border: 1px solid #ddd;
  border-radius: 6px;
  font-size: 1rem;
  transition: border-color 0.3s;
}

input:focus {
  outline: none;
  border-color: #ff6b35;
}

.error-message {
  color: #dc3545;
  font-size: 0.9rem;
  text-align: center;
}

.success-message {
  color: #28a745;
  font-size: 0.9rem;
  text-align: center;
}

.submit-btn {
  background-color: #ff6b35;
  color: white;
  border: none;
  padding: 0.8rem;
  border-radius: 6px;
  font-weight: 500;
  font-size: 1rem;
  cursor: pointer;
  transition: all 0.3s;
}

.submit-btn:hover {
  background-color: #e85a2a;
  transform: translateY(-1px);
}

.toggle-text {
  text-align: center;
  color: #666;
}

.toggle-text a {
  color: #ff6b35;
  text-decoration: none;
  font-weight: 500;
}

.toggle-text a:hover {
  text-decoration: underline;
}
</style> 