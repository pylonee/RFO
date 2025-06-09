from django.contrib import admin
from .models import Equipment, EquipmentType

@admin.register(EquipmentType)
class EquipmentTypeAdmin(admin.ModelAdmin):
    list_display = ('id', 'name', 'mask_sn')
    search_fields = ('name', )

@admin.register(Equipment)
class EquipmentAdmin(admin.ModelAdmin):
    list_display = ('id', 'equipment_type', 'serial_number', 'created_date', 'is_deleted')
    search_fields = ('equipment_type',)
