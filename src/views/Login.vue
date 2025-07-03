<template>
  <div class="login-container">
    <div class="login-box">
      <h2>登录</h2>
      <form @submit.prevent="handleLogin">
        <div class="form-group">
          <label for="email">邮箱</label>
          <input
            type="email"
            id="email"
            v-model="email"
            required
            placeholder="请输入邮箱"
          />
        </div>
        <div class="form-group">
          <label for="password">密码</label>
          <input
            type="password"
            id="password"
            v-model="password"
            required
            placeholder="请输入密码"
          />
        </div>
        <div class="form-group">
          <button type="submit" :disabled="loading">
            {{ loading ? "登录中..." : "登录" }}
          </button>
        </div>
        <div class="form-footer">
          <router-link to="/register">还没有账号？立即注册</router-link>
          <h3 style="color: black">示例账号：user@example.com</h3>
          <h3 style="color: black">示例密码：user123</h3>
          <h3 style="color: black">(也可以自己选择注册)</h3>
        </div>
        <div v-if="errorMessage" class="error-message">
          {{ errorMessage }}
        </div>
      </form>
    </div>
  </div>
</template>

<script setup>
import { ref } from "vue";
import { useRouter } from "vue-router";
import { useUserStore } from "../stores/user";
import { userApi } from "../api/user"; // 导入API封装

const router = useRouter();
const userStore = useUserStore();

const email = ref("");
const password = ref("");
const loading = ref(false);
const errorMessage = ref("");

const handleLogin = async () => {
  // 清除之前的错误消息
  errorMessage.value = "";

  if (!email.value || !password.value) {
    errorMessage.value = "请输入邮箱和密码";
    return;
  }

  try {
    loading.value = true;

    // 使用封装的API发送请求
    const response = await userApi.login({
      email: email.value,
      password: password.value,
    });

    // 确保token被正确存储
    if (response.data && response.data.token) {
      // 使用console.log确认token的存在
      console.log("收到token:", response.data.token);

      // 明确地保存token到localStorage
      window.localStorage.setItem("token", response.data.token);

      // 验证token已保存
      console.log("保存后检查token:", window.localStorage.getItem("token"));

      // 更新用户状态
      userStore.setUser(response.data.user);
      userStore.setIsLoggedIn(true);

      // 跳转到首页或之前的页面
      await router.push("/");
    } else {
      errorMessage.value = "登录失败，服务器没有返回有效的token";
      console.error("服务器响应:", response.data);
    }
  } catch (error) {
    console.error("登录失败:", error);

    // 提取API错误信息
    if (error.response && error.response.data) {
      errorMessage.value =
        error.response.data.message || "邮箱或密码错误，或账号已被冻结";
    } else {
      errorMessage.value = "网络错误，请检查您的网络连接";
    }
  } finally {
    loading.value = false;
  }
};
</script>

<style scoped>
.login-container {
  display: flex;
  justify-content: center;
  align-items: center;
  min-height: 100vh;
  background-color: #f5f5f5;
}

.login-box {
  background: white;
  padding: 2rem;
  border-radius: 8px;
  box-shadow: 0 2px 4px rgba(0, 0, 0, 0.1);
  width: 100%;
  max-width: 400px;
}

h2 {
  text-align: center;
  margin-bottom: 2rem;
  color: #333;
}

.form-group {
  margin-bottom: 1.5rem;
}

label {
  display: block;
  margin-bottom: 0.5rem;
  color: #333;
}

input {
  width: 100%;
  padding: 0.75rem;
  border: 1px solid #ddd;
  border-radius: 4px;
  font-size: 1rem;
}

button {
  width: 100%;
  padding: 0.75rem;
  background-color: #4caf50;
  color: white;
  border: none;
  border-radius: 4px;
  font-size: 1rem;
  cursor: pointer;
  transition: background-color 0.3s;
}

button:hover {
  background-color: #388e3c;
}

button:disabled {
  background-color: #ccc;
  cursor: not-allowed;
}

.form-footer {
  text-align: center;
  margin-top: 1rem;
}

.form-footer a {
  color: #4caf50;
  text-decoration: none;
}

.form-footer a:hover {
  text-decoration: underline;
}

/* 添加错误信息样式 */
.error-message {
  color: #f44336;
  margin-top: 1rem;
  text-align: center;
}
</style>
