<template>
    <v-container>
        <v-form @submit.prevent="login">
            <v-text-field
                v-model="credentials.username"
                id="qwe"
                width="300px"
                label="Логин"
            ></v-text-field>

            <v-text-field
                v-model="credentials.password"
                width="300px"
                label="Пароль"
                type="password"
            ></v-text-field>

            <v-btn type="submit" color="primary">Войти</v-btn>
        </v-form>
    </v-container>
</template>

<script setup>
import { ref } from "vue"
import { useRouter } from "vue-router"
import api from "../services/api"

const credentials = ref({
    username: '',
    password: '',
})
const router = useRouter()

const login = async () => {
    try {
        const responce = await api.login(credentials.value)
        localStorage.setItem('token', responce.data.access)
        router.push({ name: 'equipment' })
    } catch (error) {
        console.error("Ошибка входа: ", error)
    }
}
</script>