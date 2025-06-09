from .models import Equipment, EquipmentType
from .validation import validate_sn_by_mask
from django.core.exceptions import ValidationError

class EquipmentService:
    @staticmethod
    def create_equipment(data: dict) -> dict:
        # создание оборудования

        successes = []
        errors = []

        for item in data:
            try:
               #eq_type = EquipmentType.objects.get(id=item['equipment_type'])
               eq_type = item['equipment_type']

               if not validate_sn_by_mask(item['serial_number'], eq_type.mask_sn):
                   raise ValidationError('Серийный номер не соответствует маске оборудования')

               if Equipment.objects.filter(
                   equipment_type=eq_type,
                   serial_number=item['serial_number']
               ).exists():
                   raise ValidationError('Для этого типа оборудования уже существует серийный номер')

               equipment = Equipment.objects.create(
                   equipment_type=eq_type,
                   serial_number=item['serial_number'],
                   note=item.get('note', '')
               )
               successes.append(equipment)

            except Exception as e:
                errors.append({
                    'data': item,
                    'error': str(e)
                })

        return {'successes': successes, 'errors': errors}