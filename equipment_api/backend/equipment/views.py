from django_filters.rest_framework import DjangoFilterBackend
from rest_framework import viewsets, status, filters
from rest_framework.response import Response
from rest_framework.permissions import IsAuthenticated, AllowAny
from .models import Equipment, EquipmentType
from .serializers import EquipmentSerial, EquipmentTypeSerial
from .services import EquipmentService

class EquipmentTypeViewSet(viewsets.ModelViewSet):
    queryset = EquipmentType.objects.all()
    serializer_class = EquipmentTypeSerial
    filter_backends = [DjangoFilterBackend, filters.SearchFilter]
    filterset_fields = ['name', 'mask_sn']
    search_fields = ['name', 'mask_sn']
    permission_classes = [IsAuthenticated]
    #permission_classes = [AllowAny]

    def get_queryset(self):
        return super().get_queryset().order_by('id')


class EquipmentViewSet(viewsets.ModelViewSet):
    queryset = Equipment.objects.all()
    serializer_class = EquipmentSerial
    filter_backends = [DjangoFilterBackend, filters.SearchFilter]
    filterset_fields = ['equipment_type', 'serial_number']
    search_fields = ['serial_number', 'note']
    permission_classes = [IsAuthenticated]
    #permission_classes = [AllowAny]

    def get_queryset(self):
        return Equipment.objects.filter(is_deleted = False).order_by('-created_date')

    def create(self, request, *args, **kwargs):
        serializer = self.get_serializer(data=request.data, many=True)
        if not serializer.is_valid():
            return Response(serializer.errors, status=status.HTTP_400_BAD_REQUEST)

        result = EquipmentService.create_equipment(serializer.validated_data)
        if result['errors']:
            return Response({
                'message': 'Некоторые данные не прошли валидацию',
                'errors': result['errors']
            }, status=status.HTTP_207_MULTI_STATUS)

        return Response(
            EquipmentSerial(result['successes'], many=True).data,
            status=status.HTTP_201_CREATED
        )

    def destroy(self, request, *args, **kwargs):
        #
        equipment = self.get_object()
        equipment.is_deleted = True
        equipment.save()
        return Response(status=status.HTTP_204_NO_CONTENT)




