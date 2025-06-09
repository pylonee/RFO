import axios from "axios";

const api = axios.create({
    baseURL: "http://127.0.0.1:8000/api",
    headers: {
        'Content-Type': 'application/json'
    }
})

api.interceptors.request.use(config => {
    const token = localStorage.getItem('token')
    if(token){
        config.headers.Authorization = `Bearer ${token}`
    }
    return config
}, error => {
    return Promise.reject(error)
})

export default {
    getEquipment(params) {
        return api.get('/equipment/', { params })
    },
    createEquipment(data) {
        return api.post('/equipment/', data)
    },
    updateEquipment(id, data){
        return api.put(`/equipment/${id}/`, data)
    },
    deleteEquipment(id){
        return api.delete(`/equipment/${id}/`)
    },
    getEquipmentTypes(){
        return api.get('/equipment-type/')
    },

    login(credentials){
        return api.post('/user/login/', credentials)
    }
}



// export default axios.create({
//     baseURL: "http://127.0.0.1:8000/api"
// })