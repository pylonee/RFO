<template>
    <v-dialog v-model="dialogModel" max-width="500px">
        <v-card>
            <v-card-title>
                <span class="text-h5">Редактирование оборудования</span>
            </v-card-title>
            <v-card-text>
                <v-container>
                    <v-text-field
                        :model-value="props.editedItem.serial_number"
                        @update:model-value="emit('update:editedItem', {...props.editedItem, serial_number: $event})"
                        label="Серийный номер"
                    ></v-text-field> <!-- v-model="editedItem.serial_number" label="Серийный номер" -->
                    <v-textarea
                        :model-value="props.editedItem.note"
                        @update:model-value="emit('update:editedItem', {...props.editedItem, note: $event})"
                        label="Примечание"
                    ></v-textarea> <!-- v-model="editedItem.note" -->
                </v-container>
            </v-card-text>
            <v-card-actions>
                <v-spacer></v-spacer>
                <v-btn color="blue darken-1" text @click="close">Отмена</v-btn>
                <v-btn color="blue darken-1" text @click="save">Сохранить</v-btn>
            </v-card-actions>
        </v-card>
    </v-dialog>
</template>

<script setup>
import { ref, watch, defineProps, defineEmits } from 'vue'

const props = defineProps({
    dialog: Boolean,
    editedItem: Object
})

const emit = defineEmits(['update:dialog', 'update:editedItem', 'save'])

const dialogModel = ref(props.dialog)

watch(() => props.dialog, (newVal) => {
    dialogModel.value = newVal
})

watch(dialogModel, (newVal) => {
    emit('update:dialog', newVal)
})

const close = () => {
    emit('update:dialog', false)
}

const save = () => {
    emit('save', props.editedItem)
    close()
}
</script>