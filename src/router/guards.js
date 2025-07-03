import { useUserStore } from "../stores/user";

export function setupRouterGuards(router) {
  router.beforeEach(async (to, from, next) => {
    const userStore = useUserStore();
    const token = localStorage.getItem("token");

    // 判断是否需要登录权限
    const requiresAuth = to.matched.some((record) => record.meta.requiresAuth);

    // 如果本地存储中有token，但store中没有登录状态，尝试自动登录
    if (token && !userStore.isLoggedIn) {
      try {
        await userStore.checkAuthState();
      } catch (error) {
        console.error("自动登录失败:", error);
      }
    }

    // 重新检查登录状态
    if (requiresAuth && !userStore.isLoggedIn) {
      // 需要登录但未登录，重定向到登录页
      next({ path: "/login", query: { redirect: to.fullPath } });
    } else if (to.path === "/login" && userStore.isLoggedIn) {
      // 已登录访问登录页，重定向到首页
      next({ path: "/" });
    } else {
      // 正常导航
      next();
    }
  });
}
