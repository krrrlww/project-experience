import axios from "axios";

// API基础URL配置
const API_BASE_URL = "http://115.190.111.69:11012/api";

// 创建axios实例
const apiClient = axios.create({
  baseURL: API_BASE_URL,
  headers: {
    "Content-Type": "application/json",
  },
  timeout: 10000,
});

// 请求拦截器 - 在请求发送前添加token
apiClient.interceptors.request.use(
  (config) => {
    const token = localStorage.getItem("token");
    console.log(`API请求 [${config.method.toUpperCase()}] ${config.url}`);
    console.log("当前token状态:", token ? "存在" : "不存在");

    if (token) {
      config.headers["Authorization"] = `Bearer ${token}`;
    }
    return config;
  },
  (error) => {
    console.error("API请求准备阶段错误:", error);
    return Promise.reject(error);
  }
);

// 响应拦截器 - 处理响应和错误
apiClient.interceptors.response.use(
  (response) => {
    console.log(
      `API响应 [${response.config.method.toUpperCase()}] ${
        response.config.url
      }:`,
      response.status
    );
    return response;
  },
  (error) => {
    if (error.response) {
      console.error(
        `API错误 [${error.config.method.toUpperCase()}] ${error.config.url}:`,
        error.response.status
      );

      if (error.response.status === 401) {
        console.warn("认证失败，可能需要重新登录");
      }
    } else if (error.request) {
      console.error("API请求发送后未收到响应:", error.request);
    } else {
      console.error("API请求配置错误:", error.message);
    }

    return Promise.reject(error);
  }
);

// 用户API接口封装
export const userApi = {
  /**
   * 用户注册
   * @param {Object} userData 用户数据
   * @returns {Promise}
   */
  register: (userData) => {
    return apiClient.post("/user/register", userData);
  },

  /**
   * 用户登录
   * @param {Object} credentials 登录凭证
   * @returns {Promise}
   */
  login: (credentials) => {
    return apiClient.post("/user/login", credentials);
  },

  /**
   * 获取用户个人信息
   * @returns {Promise}
   */
  getProfile: () => {
    return apiClient.get("/user/profile");
  },

  /**
   * 获取用户交易记录
   * @param {Object} params 分页参数
   * @returns {Promise}
   */
  getTransactions: (params = { page: 1, per_page: 10 }) => {
    return apiClient.get("/user/transactions", { params });
  },

  /**
   * 用户账户充值
   * @param {Object} data 充值数据
   * @returns {Promise}
   */
  deposit: (data) => {
    return apiClient.post("/transaction/deposit", data);
  },

  /**
   * 用户账户提现
   * @param {Object} data 提现数据
   * @returns {Promise}
   */
  withdraw: (data) => {
    return apiClient.post("/transaction/withdraw", data);
  },

  /**
   * 用户消费
   * @param {Object} data 消费数据
   * @returns {Promise}
   */
  consume: (data) => {
    return apiClient.post("/transaction/consume", data);
  },

  /**
   * 用户登出
   * @returns {Promise}
   */
  logout: () => {
    return apiClient.post("/user/logout");
  },
};

export default apiClient;
