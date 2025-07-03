/**
 * 用于调试本地存储问题的工具函数
 */

// 在页面加载时检查localStorage
export function checkLocalStorage() {
  console.log("页面加载: 检查localStorage中的token");
  const token = localStorage.getItem("token");
  console.log("当前token状态:", token ? "存在" : "不存在", token);
}

// 设置localStorage监听，监测变化
export function monitorLocalStorage() {
  // 保存原始的localStorage.setItem方法
  const originalSetItem = localStorage.setItem;

  // 重写setItem方法
  localStorage.setItem = function (key, value) {
    console.log(`LocalStorage设置: ${key} = ${value.substring(0, 20)}...`);
    // 调用原始方法
    originalSetItem.apply(this, arguments);
  };

  // 保存原始的localStorage.removeItem方法
  const originalRemoveItem = localStorage.removeItem;

  // 重写removeItem方法
  localStorage.removeItem = function (key) {
    console.log(`LocalStorage删除: ${key}`);
    // 调用原始方法
    originalRemoveItem.apply(this, arguments);
  };

  console.log("localStorage监控已启动");
}
