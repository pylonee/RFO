Equipment API

******** Структура проекта:
equipment_api
- backend		Django проект
    - backend		настройки
    - equipment		приложение
        - admin		админ данные
        - models	модели данных
        - serializers	сериализаторы
        - services	сервисы (создание)
        - urls		маршруты
        - validation	валидация
        - views		API-контроллеры
    - frontend			Vue проект
        - src			
            - components	компоненты
            - router		маршруты
            - services		API
            - views		Страницы
            - App.vue		Главный проект

******** Основные возможности:
- CRUD операции
- управление типами оборудования
- валидация серийных номеров по маске
- JWT аутентификация
- фильтрация, поиск, пагинация

************* secretkey в equipment_api\backend\backend\settings.py НЕ ЗАПОЛНЕН!!!

******** Бэкенд:
- Python 3.13
- Django 5.2.1
- Django rest framework 3.16.0
- Django rest framework simple jwt 5.5.0
- django filter 25.1
- PyMySQL 1.1.1

******** Фронтенд:
- Vue.js
- Vuetify
- Axios
- Vue-router


******** Настройка MySQL:
- создание БД:
CREATE DATABASE equipment_db


******** Настройка бэкенда:
cd backend

- установка зависимостей:
pip install -r requirements.txt

- если будут проблемы с CORS:
pip install django-cors-headers
  в equipment_api\backend\backend\settings.py раскомментировать:
INSTALLED_APPS = [
	...
	#'corsheaders', 46 строка
	...
]

MIDDLEWARE = [
	...
	'corsheaders.middleware.CorsMiddleware', 53 строка
	...
]

61-74 строки
CORS_ALLOWED_ORIGINS полностью
CORS_ALLOW_METHODS полностью
CORS_ALLOW_CREDENTIALS = True


******** Настройка БД (equipment_api\backend\backend\settings.py):
DATABASES = {
    'default': {
        'ENGINE': 'django.db.backends.mysql',
        'NAME': 'equipment_db',
        'USER': 'ваш пользователь',
        'PASSWORD': 'ваш пароль',
        'HOST': 'localhost',
        'PORT': '3306',
    }
}

- миграции данных:
python manage.py migrate

- Супер пользователь:
python manage.py createsuperuser

- Запуск сервера:
python manage.py runserver


******** Найстройка фронтенда:
cd frontend

- установка зависимостей:
npm install

- Запуск сервера:
npm run serve


******** Доступ:
бэкенд: http://localhost:8000
фронтенд: http://localhost:8080
админ панель: http://localhost:8000/admin


