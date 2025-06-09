from rest_framework import serializers
from .models import EquipmentType, Equipment

class EquipmentTypeSerial(serializers.ModelSerializer):
    class Meta:
        model = EquipmentType
        fields = ['id', 'name', 'mask_sn']

class EquipmentSerial(serializers.ModelSerializer):
    equipment_type = EquipmentTypeSerial(read_only=True)
    equipment_type_id = serializers.PrimaryKeyRelatedField(
        queryset=EquipmentType.objects.all(),
        source='equipment_type',
        write_only=True
    )

    class Meta:
        model = Equipment
        fields = [
            'id',
            'equipment_type',
            'equipment_type_id',
            'serial_number',
            'note',
            'created_date'
        ]
        extra_kwargs = {'created_at': {'read_only': True}}