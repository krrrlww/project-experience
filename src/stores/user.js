import { defineStore } from "pinia";
import { userApi } from "../api/user";

// 确保pinia store使用正确的格式
export const useUserStore = defineStore("user", {
  // 状态定义
  state: () => ({
    user: JSON.parse(localStorage.getItem("user")) || null,
    isLoggedIn: !!localStorage.getItem("token"),
    token: localStorage.getItem("token") || null,
  }),

  // getters
  getters: {
    getUserName: (state) => state.user?.username || "游客",
    getUserEmail: (state) => state.user?.email || "",
    getUserBalance: (state) => state.user?.balance || 0,
    isAccountActive: (state) => state.user?.isActive !== false,
  },

  // actions
  actions: {
    // 设置用户信息
    setUser(user) {
      console.log("设置用户信息:", user);
      this.user = user;

      // 同步到localStorage
      if (user) {
        localStorage.setItem("user", JSON.stringify(user));
      } else {
        localStorage.removeItem("user");
      }
    },

    // 设置登录状态
    setIsLoggedIn(status) {
      console.log("设置登录状态:", status);
      this.isLoggedIn = status;
    },

    // 设置token
    setToken(token) {
      console.log(
        "设置token:",
        token ? `${token.substring(0, 10)}...` : "null"
      );
      this.token = token;

      // 同步到localStorage
      if (token) {
        localStorage.setItem("token", token);
      } else {
        localStorage.removeItem("token");
      }
    },

    // 检查认证状态并恢复会话
    async checkAuthState() {
      console.log("检查认证状态");

      // 从localStorage获取token
      const token = localStorage.getItem("token");
      console.log("localStorage中的token:", token ? "存在" : "不存在");

      if (!token) {
        this.setIsLoggedIn(false);
        this.setUser(null);
        this.setToken(null);
        return false;
      }

      // 保存到store状态
      this.token = token;

      try {
        // 使用token获取用户信息
        console.log("使用token获取用户信息");
        const response = await userApi.getProfile();
        
        // 调试输出完整响应
        console.log("API响应数据结构:", response.data);

        // 修改：检查response.data.data.user而不是response.data.user
        if (response.data && response.data.data && response.data.data.user) {
          console.log("成功获取用户信息");
          this.setUser(response.data.data.user);
          this.setIsLoggedIn(true);
          return true;
        } else {
          console.warn("API响应没有包含用户信息");
          // 不要立即logout，可能是临时问题
          this.setIsLoggedIn(false);
          return false;
        }
      } catch (error) {
        console.error("验证token失败:", error);
        // 区分不同类型的错误
        if (error.response && error.response.status === 401) {
          // 只有明确的token无效时才清除
          if (
            error.response.data &&
            error.response.data.message === "Invalid token"
          ) {
            console.log("认证失败，清除token");
            this.logout();
          } else {
            console.log("401错误但保留token，可能是临时问题");
            // 保留token但设置为未登录状态
            this.setIsLoggedIn(false);
          }
        } else {
          console.log("网络或服务器错误，保留token");
          // 保留token，可能是网络问题
          this.setIsLoggedIn(false);
        }
        return false;
      }
    },

    // 登录方法
    async login(email, password) {
      try {
        const response = await userApi.login({ email, password });

        if (response.data && response.data.token) {
          console.log("登录成功，获取到token");

          // 确保token正确保存
          this.setToken(response.data.token);
          this.setUser(response.data.user);
          this.setIsLoggedIn(true);

          // 再次验证token是否保存到localStorage
          const storedToken = localStorage.getItem("token");
          console.log(
            "验证localStorage中的token:",
            storedToken ? "存在" : "不存在"
          );

          return true;
        }
        return false;
      } catch (error) {
        console.error("登录请求失败:", error);
        return false;
      }
    },

    // 登出方法
    async logout() {
      try {
        if (this.isLoggedIn && this.token) {
          await userApi
            .logout()
            .catch((err) => console.error("登出API调用失败:", err));
        }
      } finally {
        // 无论API是否成功，都清除本地状态
        this.setToken(null);
        this.setUser(null);
        this.setIsLoggedIn(false);
      }
    },

    // 初始化用户方法
    async initUser() {
      console.log("初始化用户状态");
      const token = localStorage.getItem("token");

      if (token && !this.isLoggedIn) {
        console.log("发现token，尝试恢复会话");
        return await this.checkAuthState();
      }

      console.log("没有token或用户已登录，无需恢复会话");
      return this.isLoggedIn;
    },
  },
});
