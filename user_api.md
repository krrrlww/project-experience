# 用户管理系统 API 接口文档

## 认证机制

本系统使用JWT（JSON Web Token）进行API认证。用户或管理员登录后会获得一个访问令牌（token），后续所有需要身份验证的API请求都需要在请求头中携带此令牌。

**认证请求头格式**:
```
Authorization: Bearer <token>
```

## 目录

- [用户接口](#用户接口)
  - [用户注册](#用户注册)
  - [用户登录](#用户登录)
  - [用户登出](#用户登出)
  - [获取用户信息](#获取用户信息)
  - [获取用户交易记录](#获取用户交易记录)
- [管理员接口](#管理员接口)
  - [管理员注册](#管理员注册)
  - [管理员登录](#管理员登录)
  - [管理员登出](#管理员登出)
  - [获取所有用户信息](#获取所有用户信息)
  - [锁定用户账户](#锁定用户账户)
  - [解锁用户账户](#解锁用户账户)
  - [获取指定用户交易记录](#获取指定用户交易记录)
- [交易接口](#交易接口)
  - [账户充值](#账户充值)
  - [账户提现](#账户提现)
  - [用户消费](#用户消费)

## 用户接口

### 用户注册

- **URL**: `/api/user/register`
- **方法**: `POST`
- **描述**: 注册新用户账户
- **请求参数**:
  ```json
  {
    "username": "用户名",
    "email": "用户邮箱",
    "password": "用户密码"
  }
  ```
- **响应**:
  - 成功 (201):
    ```json
    {
      "message": "注册成功",
      "user": {
        "id": 1,
        "username": "用户名",
        "email": "用户邮箱",
        "status": "active",
        "balance": 0.0,
        "created_at": "2025-04-29T10:30:00"
      }
    }
    ```
  - 错误 (400):
    ```json
    {"error": "请提供用户名、邮箱和密码"}
    ```
    ```json
    {"error": "该邮箱已被注册"}
    ```
    ```json
    {"error": "该用户名已被使用"}
    ```

### 用户登录

- **URL**: `/api/user/login`
- **方法**: `POST`
- **描述**: 用户账户登录
- **请求参数**:
  ```json
  {
    "email": "用户邮箱",
    "password": "用户密码"
  }
  ```
- **响应**:
  - 成功 (200):
    ```json
    {
      "message": "登录成功",
      "token": "eyJhbGciOiJIUzI1NiIsInR5cCI6IkpXVCJ9...", // JWT访问令牌
      "user": {
        "id": 1,
        "username": "用户名",
        "email": "用户邮箱",
        "status": "active",
        "balance": 100.0,
        "created_at": "2025-04-29T10:30:00"
      }
    }
    ```
  - 错误 (400/401/403):
    ```json
    {"error": "请提供邮箱和密码"}
    ```
    ```json
    {"error": "邮箱或密码不正确"}
    ```
    ```json
    {"error": "账户已被锁定，请联系管理员"}
    ```

### 用户登出

- **URL**: `/api/user/logout`
- **方法**: `POST`
- **描述**: 用户退出登录
- **请求头**: 需要JWT身份验证 (`Authorization: Bearer <token>`)
- **响应**:
  - 成功 (200):
    ```json
    {"message": "退出登录成功"}
    ```

### 获取用户信息

- **URL**: `/api/user/profile`
- **方法**: `GET`
- **描述**: 获取当前登录用户的详细信息
- **请求头**: 需要JWT身份验证 (`Authorization: Bearer <token>`)
- **响应**:
  - 成功 (200):
    ```json
    {
      "user": {
        "id": 1,
        "username": "用户名",
        "email": "用户邮箱",
        "status": "active",
        "balance": 100.0,
        "created_at": "2025-04-29T10:30:00"
      }
    }
    ```

### 获取用户交易记录

- **URL**: `/api/user/transactions`
- **方法**: `GET`
- **描述**: 获取当前登录用户的交易记录
- **请求头**: 需要用户身份验证
- **请求参数**: 
  - `page`: 页码，默认1（URL参数）
  - `per_page`: 每页记录数，默认10，最大100（URL参数）
- **响应**:
  - 成功 (200):
    ```json
    {
      "transactions": [
        {
          "id": 1,
          "amount": 100.0,
          "title": "账户充值",
          "description": "首次充值",
          "date": "2025-04-29T10:35:00",
          "user_id": 1
        },
        {
          "id": 2,
          "amount": -50.0,
          "title": "账户提现",
          "description": "提现到银行卡",
          "date": "2025-04-29T11:20:00",
          "user_id": 1
        }
      ],
      "total": 10,
      "pages": 5,
      "current_page": 1
    }
    ```

## 管理员接口

### 管理员注册

- **URL**: `/api/admin/register`
- **方法**: `POST`
- **描述**: 注册新管理员账户
- **请求参数**:
  ```json
  {
    "username": "管理员用户名",
    "email": "管理员邮箱",
    "password": "管理员密码"
  }
  ```
- **响应**:
  - 成功 (201):
    ```json
    {
      "message": "注册成功",
      "admin": {
        "id": 1,
        "username": "管理员用户名",
        "email": "管理员邮箱",
        "created_at": "2025-04-29T10:30:00"
      }
    }
    ```
  - 错误 (400):
    ```json
    {"error": "请提供用户名、邮箱和密码"}
    ```
    ```json
    {"error": "该邮箱已被注册"}
    ```
    ```json
    {"error": "该用户名已被使用"}
    ```

### 管理员登录

- **URL**: `/api/admin/login`
- **方法**: `POST`
- **描述**: 管理员账户登录
- **请求参数**:
  ```json
  {
    "email": "管理员邮箱",
    "password": "管理员密码"
  }
  ```
- **响应**:
  - 成功 (200):
    ```json
    {
      "message": "登录成功",
      "admin": {
        "id": 1,
        "username": "管理员用户名",
        "email": "管理员邮箱",
        "created_at": "2025-04-29T10:30:00"
      }
    }
    ```
  - 错误 (400/401):
    ```json
    {"error": "请提供邮箱和密码"}
    ```
    ```json
    {"error": "邮箱或密码不正确"}
    ```

### 管理员登出

- **URL**: `/api/admin/logout`
- **方法**: `POST`
- **描述**: 管理员退出登录
- **请求头**: 需要管理员身份验证
- **响应**:
  - 成功 (200):
    ```json
    {"message": "退出登录成功"}
    ```

### 获取所有用户信息

- **URL**: `/api/admin/users`
- **方法**: `GET`
- **描述**: 获取系统中所有用户的信息
- **请求头**: 需要管理员身份验证
- **请求参数**: 
  - `page`: 页码，默认1（URL参数）
  - `per_page`: 每页记录数，默认10，最大100（URL参数）
- **响应**:
  - 成功 (200):
    ```json
    {
      "users": [
        {
          "id": 1,
          "username": "用户1",
          "email": "user1@example.com",
          "status": "active",
          "balance": 100.0,
          "created_at": "2025-04-29T10:30:00"
        },
        {
          "id": 2,
          "username": "用户2",
          "email": "user2@example.com",
          "status": "locked",
          "balance": 50.0,
          "created_at": "2025-04-29T11:45:00"
        }
      ],
      "total": 25,
      "pages": 3,
      "current_page": 1
    }
    ```

### 锁定用户账户

- **URL**: `/api/admin/users/{user_id}/lock`
- **方法**: `POST`
- **描述**: 锁定指定用户的账户
- **请求头**: 需要管理员身份验证
- **URL参数**: `user_id` - 用户ID
- **响应**:
  - 成功 (200):
    ```json
    {
      "message": "用户 用户名 已被锁定",
      "user": {
        "id": 1,
        "username": "用户名",
        "email": "user@example.com",
        "status": "locked",
        "balance": 100.0,
        "created_at": "2025-04-29T10:30:00"
      }
    }
    ```
  - 错误 (404):
    ```json
    {"error": "未找到该用户"}
    ```

### 解锁用户账户

- **URL**: `/api/admin/users/{user_id}/unlock`
- **方法**: `POST`
- **描述**: 解锁指定用户的账户
- **请求头**: 需要管理员身份验证
- **URL参数**: `user_id` - 用户ID
- **响应**:
  - 成功 (200):
    ```json
    {
      "message": "用户 用户名 已被解锁",
      "user": {
        "id": 1,
        "username": "用户名",
        "email": "user@example.com",
        "status": "active",
        "balance": 100.0,
        "created_at": "2025-04-29T10:30:00"
      }
    }
    ```
  - 错误 (404):
    ```json
    {"error": "未找到该用户"}
    ```

### 获取指定用户交易记录

- **URL**: `/api/admin/users/{user_id}/transactions`
- **方法**: `GET`
- **描述**: 管理员获取指定用户的交易记录
- **请求头**: 需要管理员身份验证
- **URL参数**: `user_id` - 用户ID
- **请求参数**: 
  - `page`: 页码，默认1（URL参数）
  - `per_page`: 每页记录数，默认10，最大100（URL参数）
- **响应**:
  - 成功 (200):
    ```json
    {
      "username": "用户名",
      "transactions": [
        {
          "id": 1,
          "amount": 100.0,
          "title": "账户充值",
          "description": "首次充值",
          "date": "2025-04-29T10:35:00",
          "user_id": 1
        },
        {
          "id": 2,
          "amount": -50.0,
          "title": "账户提现",
          "description": "提现到银行卡",
          "date": "2025-04-29T11:20:00",
          "user_id": 1
        }
      ],
      "total": 10,
      "pages": 5,
      "current_page": 1
    }
    ```
  - 错误 (404):
    ```json
    {"error": "未找到该用户"}
    ```

## 交易接口

### 账户充值

- **URL**: `/api/transaction/deposit`
- **方法**: `POST`
- **描述**: 用户账户充值
- **请求头**: 需要用户身份验证
- **请求参数**:
  ```json
  {
    "amount": 100.0,
    "description": "账户充值"
  }
  ```
- **响应**:
  - 成功 (200):
    ```json
    {
      "message": "充值成功",
      "transaction": {
        "id": 1,
        "amount": 100.0,
        "title": "账户充值",
        "description": "账户充值",
        "date": "2025-04-29T10:35:00",
        "user_id": 1
      },
      "new_balance": 200.0
    }
    ```
  - 错误 (400/403):
    ```json
    {"error": "请提供有效的充值金额"}
    ```
    ```json
    {"error": "账户已被锁定，无法进行交易"}
    ```

### 账户提现

- **URL**: `/api/transaction/withdraw`
- **方法**: `POST`
- **描述**: 用户账户提现
- **请求头**: 需要用户身份验证
- **请求参数**:
  ```json
  {
    "amount": 50.0,
    "description": "提现到银行卡"
  }
  ```
- **响应**:
  - 成功 (200):
    ```json
    {
      "message": "提现成功",
      "transaction": {
        "id": 2,
        "amount": -50.0,
        "title": "账户提现",
        "description": "提现到银行卡",
        "date": "2025-04-29T11:20:00",
        "user_id": 1
      },
      "new_balance": 150.0
    }
    ```
  - 错误 (400/403):
    ```json
    {"error": "请提供有效的提现金额"}
    ```
    ```json
    {"error": "账户余额不足"}
    ```
    ```json
    {"error": "账户已被锁定，无法进行交易"}
    ```

### 用户消费

- **URL**: `/api/transaction/consume`
- **方法**: `POST`
- **描述**: 记录用户消费
- **请求头**: 需要用户身份验证
- **请求参数**:
  ```json
  {
    "amount": 30.0,
    "title": "购买商品",
    "description": "购买了一本书"
  }
  ```
- **响应**:
  - 成功 (200):
    ```json
    {
      "message": "消费交易记录已创建",
      "transaction": {
        "id": 3,
        "amount": -30.0,
        "title": "购买商品",
        "description": "购买了一本书",
        "date": "2025-04-29T14:50:00",
        "user_id": 1
      },
      "new_balance": 120.0
    }
    ```
  - 错误 (400/403):
    ```json
    {"error": "请提供消费金额和消费项目名称"}
    ```
    ```json
    {"error": "请提供有效的消费金额"}
    ```
    ```json
    {"error": "账户余额不足"}
    ```
    ```json
    {"error": "账户已被锁定，无法进行交易"}
    ```

## 数据模型

系统包含三个主要的数据模型：

1. **User** - 普通用户
2. **Admin** - 管理员用户
3. **Transaction** - 交易记录

## 系统启动

```bash
# 初始化数据库
flask init-db

# 创建默认管理员账户
flask create-admin

# 启动应用
flask run
```

默认管理员账户：
- 邮箱：admin@example.com
- 密码：admin123

_文档更新日期：2025年4月29日_