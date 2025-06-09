<template>
    <v-form @submit.prevent="submit">
        <v-select
            v-model="form.equipment_type_id"
            :items="equipmentTypes"
            item-title="name"
            item-value="id"
            label="Тип оборудования"
            required
        ></v-select>

        <v-textarea
            v-model="form.serial_numbers"
            label="Серийные номера"
            required
        ></v-textarea>
        
        <v-textarea
            v-model="form.note"
            label="Примечание"
        ></v-textarea>
        
        <v-btn type="submit" color="primary">Добавить</v-btn>
    </v-form>
</template>

<script setup>
import { ref, defineProps, defineEmits } from 'vue' // { ref, defineProps, defineEmits }
import api from '../services/api'

const props = defineProps({
    equipmentTypes: Array
})

const equipmentTypes = ref(props.equipmentTypes)

const emit = defineEmits(['created'])

const form = ref ({
    equipment_type_id: null,
    serial_numbers: '',
    note: ''
})

const submit = async () => {
    const serials = form.value.serial_numbers.split('\n')
    .map(sn => sn.trim())
    .filter(sn => sn.length > 0)

    const data = serials.map(serial_number => ({
        equipment_type_id: form.value.equipment_type_id,
        serial_number,
        note: form.value.note
    }))

    try {
        await api.createEquipment(data)
        emit('created')

        form.value = { equipment_type_id: null, serial_numbers: '', note: '' }
    } catch (error) {
        console.error("Ошибка при добавлении оборудования: ", error)
    }
}
</script>