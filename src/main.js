import { createApp } from "vue";
import { createPinia } from "pinia";
import App from "./App.vue";
import router from "./router";
import ElementPlus from "element-plus";
import "element-plus/dist/index.css";
import * as ElementPlusIconsVue from "@element-plus/icons-vue";

// 创建应用实例
const app = createApp(App);
const pinia = createPinia();

// 注册Element Plus
app.use(ElementPlus, { size: "default", zIndex: 2000 });

// 注册所有图标
for (const [key, component] of Object.entries(ElementPlusIconsVue)) {
  app.component(key, component);
}

app.use(pinia);

// 改为普通import，避免顶级await
import { useUserStore } from "./stores/user";

// 初始化函数
function initApp() {
  const userStore = useUserStore();

  // 在路由之前先检查用户认证状态
  if (localStorage.getItem("token")) {
    console.log("应用初始化: 检测到token，尝试恢复用户会话");

    userStore.checkAuthState().catch((error) => {
      console.error("认证状态检查失败:", error);
      // 只有在确认是无效token的情况下才清除
      if (
        error.response &&
        error.response.status === 401 &&
        error.response.data &&
        error.response.data.message === "Invalid token"
      ) {
        console.log("清除无效token");
        localStorage.removeItem("token");
        localStorage.removeItem("user");
      } else {
        console.log("保留token，可能是网络或服务器暂时性问题");
        // 设置基本的认证状态，即使API调用失败
        userStore.token = localStorage.getItem("token");
        userStore.isLoggedIn = true;

        // 尝试从本地存储恢复用户信息
        const cachedUser = localStorage.getItem("user");
        if (cachedUser) {
          try {
            userStore.user = JSON.parse(cachedUser);
            console.log("从本地缓存恢复用户信息:", userStore.user);
          } catch (e) {
            console.error("解析缓存的用户信息失败:", e);
          }
        }
      }
    });
  }

  // 设置路由守卫
  router.beforeEach((to, from, next) => {
    const requiresAuth = to.matched.some((record) => record.meta.requiresAuth);
    const isLoggedIn = userStore.isLoggedIn;
    const hasToken = !!localStorage.getItem("token");

    console.log(
      "路由守卫: 路径=",
      to.path,
      "需要认证=",
      requiresAuth,
      "已登录=",
      isLoggedIn,
      "有Token=",
      hasToken
    );

    if (requiresAuth && !isLoggedIn && !hasToken) {
      console.log("需要登录权限，重定向到登录页");
      next("/login");
    } else {
      next();
    }
  });

  app.use(router);

  // 挂载应用
  app.mount("#app");
}

// 启动应用
initApp();

// 辅助函数：监控localStorage变化
const originalSetItem = localStorage.setItem;
localStorage.setItem = function (key, value) {
  if (key === "token") {
    console.log(`设置token: ${value.substring(0, 10)}...`);
  }
  originalSetItem.apply(this, arguments);
};

const originalRemoveItem = localStorage.removeItem;
localStorage.removeItem = function (key) {
  if (key === "token") {
    console.log("移除token");
  }
  originalRemoveItem.apply(this, arguments);
};
