<template>
    <v-container>
        <h1>Оборудование</h1>

        <v-btn @click="showForm = !showForm">
            {{ showForm ? 'Скрыть форму' : 'Добавить оборудование' }}
        </v-btn>

        <v-expand-transition>
            <EquipmentForm
                v-if="showForm"
                :equipmentTypes="equipmentTypes"
                @created="fetchEquipment"
            />
        </v-expand-transition>

        <EquipmentList
            :equipment="equipment"
            :totalPages="totalPages"
            :search="search"
            @edit="editEquipment"
            @delete="deleteEquipment"
            @update:page="setPage"
            @update:search="setSearch"
        /><!-- @update:search="setSearch" -->

        <EquipmentEditDialog
            v-model:dialog="editDialog"
            :editedItem="editedItem"
            @save="updateEquipment"
        />
    </v-container>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import EquipmentForm from '../components/EquipmentForm.vue'
import EquipmentList from '../components/EquipmentList.vue'
import EquipmentEditDialog from '../components/EquipmentEditDialog.vue'
import api from '../services/api'

const showForm = ref(false)
const equipment = ref([])
const equipmentTypes = ref([])
const totalPages = ref(1)
const page = ref(1)
const search = ref('')
const editDialog = ref(false)
const editedItem = ref({})

onMounted(() => {
    fetchEquipment()
    fetchEquipmentTypes()
})

const fetchEquipment = async () => {
    try {
        const params = {
            page: page.value,
            search: search.value,
        }
        const response = await api.getEquipment(params)
        equipment.value = response.data.results
        totalPages.value = Math.ceil(response.data.count/20)
    } catch (error) {
        console.error('Ошибка загрузки оборудования: ', error)
    }
}

const fetchEquipmentTypes = async () => {
    try {
        const response = await api.getEquipmentTypes()
        equipmentTypes.value = response.data.results
    } catch (error) {
        console.error('Ошибка загрузки типов оборудования: ', error)
    }
}

const setPage = (newPage) => {
    page.value = newPage
    fetchEquipment()
}

const setSearch = (newSearch) => {
    search.value = newSearch
    page.value = 1
    fetchEquipment()
}

const editEquipment = (item) => {
    editedItem.value = {...item}
    editDialog.value = true
}

const updateEquipment = async (item) => {
    try {
        await api.updateEquipment(item.id, {
            serial_number: item.serial_number,
            note: item.note
        })
        fetchEquipment()
    } catch (error) {
        console.error('Ошибка обновления оборудования', error)
    }
}

const deleteEquipment = async (id) => {
    if (confirm('Вы уверены, что хотите удалить оборудование?')){
        try {
            await api.deleteEquipment(id)
            fetchEquipment()
        } catch (error) {
            console.error('Ошибка удаления оборудования: ', error)
        }
    }
}
</script>