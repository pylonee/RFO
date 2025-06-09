<template>
    <v-container>
        <!-- заголовок, добавление -->
         <v-row class="mb4" align="center">
            <v-col cols="12" md="6">
                <h1 class="text-h4">Управление оборудованием</h1>
            </v-col>
            <v-col cols="12" md="6" class="text-md-right">
                <v-btn
                    color="primary"
                    @click="showAddDialog = true"
                    prepend-icon="mdi-plus"
                >
                    Добавить оборудование
                </v-btn>
            </v-col>
         </v-row>

         <!-- фильтры -->
          <v-card class="mb-6">
            <v-card-text>
                <v-row>
                    <v-col cols="12" md="6">
                        <v-text-field
                            v-model="searchQuery"
                            label="Поиск по серийному номеру"
                            clearable
                            @update:modelValue="fetchEquipment"
                        ></v-text-field>
                    </v-col>
                    <v-col cols="12" md="6">
                        <v-select
                            v-model="selectedType"
                            :items="equipmentTypes"
                            item-title="name"
                            item-value="id"
                            label="Тип оборудования"
                            clearable
                            @update:modelValue="fetchEquipment"
                        ></v-select>
                    </v-col>
                </v-row>
            </v-card-text>
          </v-card>

          <!-- таблица оборудования -->
           <v-card>
                <v-data-table
                    :headers="headers"
                    :items="equipment"
                    :loading="loading"
                    no-data-text="Оборудование не найдено"
                >
                    <template v-slot:[`item.actions`]="{ item }">
                        <!-- <template #item.actions="{ item }"> -->
                        <v-btn
                            icon="mdi-pencil"
                            variant="text"
                            color="primary"
                            @click="editItem(item)"
                        ></v-btn>
                        <v-btn
                            icon="mdi-delete"
                            variant="text"
                            color="error"
                            @click="confirmDelete(item.id)"
                        ></v-btn>
                    </template>
                </v-data-table>
           </v-card>

           <!-- добавление\редактирование -->
            <v-dialog v-model="showAddDialog" max-width="600">
                <v-card>
                    <v-card-title>
                        {{ editMode ? 'Редактирование' : 'Добавление' }}
                    </v-card-title>
                    <v-card-text>
                        <v-form @submit.prevent="saveEquipment">
                            <v-select
                                v-model="currentItem.equipment_type"
                                :items="equipmentTypes"
                                item-title="name"
                                item-value="id"
                                label="Тип оборудования"
                                :rules="[v => !!v || 'Обязательное поле']"
                                required
                            ></v-select> <!-- v-model="currentItem.equipment_type_id" -->

                            <v-text-field
                                v-model="currentItem.serial_number"
                                label="Серийный номер"
                                :rules="[v => !!v || 'Обязательное поле']"
                                required
                            ></v-text-field>

                            <v-textarea
                                v-model="currentItem.note"
                                label="Примечание"
                                rows="2"
                            ></v-textarea>

                            <v-card-actions class="justify-end">
                                <v-btn
                                    variant="text"
                                    @click="showAddDialog = false"
                                >
                                    Отмена
                                </v-btn>
                                <v-btn
                                    color="primary"
                                    type="submit"
                                    :loading="saving"
                                >
                                    Сохранить
                                </v-btn>
                            </v-card-actions>
                        </v-form>
                    </v-card-text>
                </v-card>
            </v-dialog>

            <!-- подтверждение удаления -->
             <v-dialog v-model="showDeleteDialog" max-width="400">
                <v-card>
                    <v-card-title>Подтверждение удаления</v-card-title>
                    <v-card-text>
                        Вы уверены, что хотите удалить это оборудование?
                    </v-card-text>
                    <v-card-actions>
                        <v-spacer></v-spacer>
                        <v-btn
                            variant="text"
                            @click="showDeleteDialog = false"
                        >
                            Отмена
                        </v-btn>
                        <v-btn
                            color="error"
                            @click="deleteEquipment"
                            :loading="deleting"
                        >
                            Удалить
                        </v-btn>
                    </v-card-actions>
                </v-card>
             </v-dialog>
    </v-container>
</template>

<script setup>
import { ref, onMounted } from 'vue'
import api from '@/services/api'


const equipment = ref([])
const equipmentTypes = ref([])
const searchQuery = ref('')
const selectedType = ref(null)
const loading = ref(false)
const saving = ref(false)
const deleting = ref(false)
const showAddDialog = ref(false)
const showDeleteDialog = ref(false)
const editMode = ref(false)
const currentItemId = ref(null)

const currentItem = ref({
    equipment_type_id: null,
    quipment_type: '',
    serial_number: '',
    note: ''
})

const headers = [
    {title: 'ID', key: 'id'},
    {title: 'Тип оборудования', key: 'equipment_type.name'},
    {title: 'Серийный номер', key: 'serial_number'},
    {title: 'Примечание', key: 'note'},
    {title: 'Действия', key: 'actions', sortable: false},
]

const fetchEquipment = async () => {
    try {
        loading.value = true
        const params = {
            search: searchQuery.value,
            equipment_type: selectedType.value || undefined
        }
        const response = await api.getEquipment(params)
        equipment.value = response.data.results
    } catch (error) {
        console.error('Ошибка загрузки оборудования: ', error)
    } finally {
        loading.value = false
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

const editItem = (item) => {
    editMode.value = true
    currentItemId.value = item.id
    currentItem.value = {
        equipment_type_id: item.equipment_type_id?.id,
        equipment_type: item.equipment_type.name,
        serial_number: item.serial_number,
        note: item.note
    }
    showAddDialog.value = true
}

const confirmDelete = (id) => {
    currentItemId.value = id
    showDeleteDialog.value = true
}

const saveEquipment = async () => {
    try {
        saving.value = true
        if (editMode.value) {
            await api.updateEquipment(currentItemId.value, currentItem.value)
        } else {
            console.log(currentItem.value)
            await api.createEquipment([currentItem.value])
        }
        showAddDialog.value = false
        resetForm()
        fetchEquipment()
    } catch (error) {
        console.error('Ошибка сохранения: ', error.response?.data || error.message)
    } finally {
        saving.value = false
    }
}

const deleteEquipment = async () => {
    try {
        deleting.value = true
        await api.deleteEquipment(currentItemId.value)
        showDeleteDialog.value = false
        fetchEquipment()
    } catch (error) {
        console.error('Ошибка удаления: ', error)
    } finally {
        deleting.value = false
    }
}

const resetForm = () => {
    currentItem.value = {
        equipment_type_id: null,
        serial_number: '',
        note: ''
    }
    currentItemId.value = null
    editMode.value = false
}

onMounted(() => {
    fetchEquipment()
    fetchEquipmentTypes()
})
</script>

<style scoped>
.v-data-table {
    margin-top: 10px;
}
</style>