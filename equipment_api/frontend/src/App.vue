<template>
  <v-app>
    <v-app-bar app color="primary" dark>
      <v-toolbar-title>Управление оборудованием</v-toolbar-title>
      <v-spacer></v-spacer>
      <v-btn v-if="isAuthenticated" @click="logout">Выйти</v-btn>
    </v-app-bar>

    <v-main>
      <router-view></router-view>
    </v-main>
  </v-app>
</template>

<script setup>
import { computed } from 'vue'
import { useRouter } from 'vue-router'

const router = useRouter()

const isAuthenticated = computed(() => {
  return localStorage.getItem('token') !== null
})

const logout = () => {
  localStorage.removeItem('token')
  router.push({name: 'login' })
}
</script>

<style>
#app {
  font-family: Avenir, Helvetica, Arial, sans-serif;
  text-align: left;
  margin-top: 20px;
}
</style>
