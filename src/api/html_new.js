import axios from "axios";
// API基础URL配置
const API_BASE_URL = "http://115.190.111.69:11012";
// 封装axios实例
const api = axios.create({
    baseURL: API_BASE_URL,
    timeout: 5000, // 请求超时时间
});
// 请求拦截器 - 在请求发送前添加token
api.interceptors.request.use(
    (config) => {
        const token = localStorage.getItem("token");
        console.log(`API请求 [${config.method.toUpperCase()}] ${config.url}`);
        console.log("当前token状态:", token ? "存在" : "不存在");

        if (token) {
            config.headers["Authorization"] = `Bearer ${token}`;
        }
        // 根据请求数据类型自动设置 Content-Type
        if (config.data instanceof FormData) {
            // 处理文件上传，不设置 Content-Type，让浏览器自动设置为 multipart/form-data
            delete config.headers['Content-Type'];
        } else {
            // 其他情况默认使用 JSON
            config.headers['Content-Type'] = 'application/json';
        }
        return config;
    },
    (error) => {
        console.error("API请求准备阶段错误:", error);
        return Promise.reject(error);
    }
);

// 响应拦截器 - 处理响应和错误
api.interceptors.response.use(
    (response) => {
        console.log(
            `API响应 [${response.config.method.toUpperCase()}] ${response.config.url
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