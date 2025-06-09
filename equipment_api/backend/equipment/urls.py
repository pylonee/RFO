from django.urls import path, include
from rest_framework.routers import DefaultRouter
from .views import EquipmentViewSet, EquipmentTypeViewSet
from rest_framework_simplejwt.views import TokenObtainPairView

router = DefaultRouter()
router.register(r'equipment', EquipmentViewSet, basename='equipment')
router.register(r'equipment-type', EquipmentTypeViewSet, basename='equipment-type')

urlpatterns=[
    path('', include(router.urls)),
    path('user/login/', TokenObtainPairView.as_view(), name='login'),
]