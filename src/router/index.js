import { createRouter, createWebHashHistory } from "vue-router";

// 定义路由
const routes = [
  {
    path: "/",
    name: "Home",
    component: () => import("../views/Home.vue"),
    meta: { requiresAuth: true },
  },
  {
    path: "/login",
    name: "Login",
    component: () => import("../views/Login.vue"),
  },
  {
    path: "/register",
    name: "Register",
    component: () => import("../views/Register.vue"),
  },
  {
    path: "/profile",
    name: "Profile",
    component: () => import("../views/UserProfile.vue"),
    meta: { requiresAuth: true },
  },
  {
    path: "/usepage",
    name: "UsePage",
    component: () => import("../views/UsePage.vue"),
    meta: { requiresAuth: true },
  },
  {
    path: "/results",
    name: "Results",
    component: () => import("../views/Results.vue"),
    meta: { requiresAuth: true },
  },
  {
    path: "/docs",
    name: "Docs",
    component: () => import("../views/Docs.vue"),
  },
  {
    path: "/admin",
    name: "Admin",
    component: () => import("../views/Admin.vue"),
    meta: { requiresAuth: true, isAdmin: true },
  },
  // 处理不匹配的路由
  {
    path: "/:pathMatch(.*)*",
    redirect: "/",
  },
];

// 创建路由实例
const router = createRouter({
  history: createWebHashHistory(),
  routes,
});

// 全局前置守卫
router.beforeEach((to, from, next) => {
  const token = localStorage.getItem("token");
  const requiresAuth = to.matched.some((record) => record.meta.requiresAuth);

  if (requiresAuth && !token) {
    next("/login");
  } else if (to.path === "/login" && token) {
    next("/");
  } else {
    next();
  }
});

export default router;
