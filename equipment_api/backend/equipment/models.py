from django.db import models
from django.utils import timezone

class EquipmentType(models.Model):
    name = models.CharField("Наименование типа", max_length=100, unique=True)
    mask_sn = models.CharField("Маска серийного номера", max_length=20, default="")

    objects = models.Manager()

    def __str__(self):
        return self.name

class Equipment(models.Model):
    equipment_type = models.ForeignKey(
        EquipmentType,
        on_delete=models.CASCADE
    )
    serial_number = models.CharField("Серийный номер", max_length=50)
    note = models.TextField("Примечание", blank=True)
    created_date = models.DateTimeField("Дата создания", default=timezone.now)
    is_deleted = models.BooleanField("Удалено", default=False)

    objects = models.Manager()

    class Meta:
        unique_together = [['equipment_type', 'serial_number']]

    def __str__(self):
        return f"{self.equipment_type} - {self.serial_number}"
