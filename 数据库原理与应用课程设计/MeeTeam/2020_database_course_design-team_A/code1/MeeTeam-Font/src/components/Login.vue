<template>
  <div id="login-container">
    <div style="text-align: center;height: 50px">
      {{toptest}}
    </div>
    <el-form :model="ruleForm" status-icon :rules="rules" ref="ruleForm" label-width="100px" class="demo-ruleForm">
      <el-form-item label="账号" prop="user">
        <el-input type="text" v-model="user" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item label="密码" prop="pass">
        <el-input type="password" v-model="pass" autocomplete="off"></el-input>
      </el-form-item>
      <el-form-item>
        <el-button type="primary" @click="submitForm('ruleForm')">提交</el-button>
        <el-button @click="resetForm('ruleForm')">重置</el-button>
      </el-form-item>
      <el-button type="text" class="testleft" @click="adminlo">{{ globaltest }}</el-button>
      <el-button type="text" class="testright" @click="adduser">注册</el-button>
      <el-button type="text" class="testright">找回密码</el-button>
    </el-form>
  </div>
</template>

<script>
import global_msg from '../utils/global.js'
import { login } from '@/api/login.js'
import { adminlogin } from '@/api/login.js'
export default {
  name: 'LogIn',
  data() {
    return {
      globaltest: "管理员登陆",
      toptest:"用户登陆",
      ifadmin: false,//当前用户是否是管理员
      user: "",
      pass: "",
      isLogin: false
    };
  },
  methods: {
    adminlo() {
      this.ifadmin = !this.ifadmin;//取反
      if (this.ifadmin == true) {
        this.globaltest = "用户登陆";
        this.toptest="管理员登陆"
      } else {
        this.globaltest = "管理员登陆";
        this.toptest="用户登陆"
      }
    },
    resetForm() {//重置表单
      this.user = ''
      this.pass = ''
    },
    //提交表单
    submitForm(formName) {
      var vm = this;
      if (this.user === "") {
        alert("请输入用户名")
        return;
      }
      if (this.pass === "") {
        alert("请输入密码")
        return;
      }
      //请求地址,this和vm指的是全局
      let params = {
        user: vm.user,
        pass: vm.pass
      }
      if (this.ifadmin == false) {
        login(params).then(function (res) {
          if (res.data === false) {
            vm.$message.error("登录失败");
            vm.resetForm(formName);
          } else {
            global_msg.nowuserid = vm.user;//改变全局nowusername
            vm.$message.success("登录成功");
            vm.$router.push({ path: "/users/InforList" }); //接下来进入到哪个路由
          }
        })
      }else{
        adminlogin(params).then(function (res) {
          if (res.data === false) {
            vm.$message.error("登录失败");
            vm.resetForm(formName);
          } else {
            global_msg.nowadminid = vm.user;//改变全局nowusername
            vm.$message.success("登录成功");
            vm.$router.push({ path: "/Admin/AdminPage" }); //接下来进入到哪个路由
          }
        })
      }
    },
    adduser() { //进入注册的界面
      this.$router.push({ path: "/users/AddUser" }); //接下来进入到哪个路由
    }
  }
}
</script>

<style>
body {
  margin: 0;
}

#login-container {
  width: 400px;
  height: 290px;
  background: #e5e9f2;
  position: absolute;
  /*绝对定位 */
  left: 50%;
  top: 50%;
  margin-left: -220px;
  margin-top: -170px;
  border-radius: 5px;
  padding-top: 40px;
  padding-right: 40px;
  padding-left: 40px;
}

.testleft {
  float: left;
}

.testright {
  float: right;
}
</style>