<template>
    <div>
        <v-text-field
            :model-value="localSearch"
            label="Поиск"
            clearable
            @update:model-value="localSearchChange"
        ></v-text-field> <!-- v-model="search" -->

        <v-table>
            <thead>
                <tr>
                    <th>ID</th>
                    <th>Тип</th>
                    <th>Серийный номер</th>
                    <th>Примечание</th>
                    <th>Действия</th>
                </tr>
            </thead>
            <tbody>
                <tr v-for="item in props.equipment" :key="item.id">
                    <td>{{ item.id }}</td>
                    <td>{{ item.equipment_type.name }}</td>
                    <td>{{ item.serial_number }}</td>
                    <td>{{ item.note }}</td>
                    <td>
                        <v-btn icon @click="editItem(item)">
                            <v-icon>mdi-pencil</v-icon>
                        </v-btn>
                        <v-btn icon @click="deleteItem(item.id)">
                            <v-icon>mdi-delete</v-icon>
                        </v-btn>
                    </td>
                </tr>
            </tbody>
        </v-table>

        <v-pagination v-model="page" :length="props.totalPages"></v-pagination>
    </div>
</template>

<script setup>
import { ref, watch, defineProps, defineEmits } from 'vue' // { ref, watch, defineProps, defineEmits }

const props = defineProps({
    equipment: Array,
    totalPages: Number,
    search: String
})

const emit = defineEmits(['Edit', 'delete', 'update:page', 'update:search'])

const localSearch = ref(props.search || '')
const page = ref(1)

const localSearchChange = (newVal) => {
    localSearch.value = newVal
    emit('update:search', newVal)
}

watch(page, (newVal) => {
    emit('update:page', newVal)
})

const editItem = (item) => {
    emit('edit', item)
}

const deleteItem = (id) => {
    emit('delete', id)
}
</script>
