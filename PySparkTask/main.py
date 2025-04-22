
#     Я не знаю pySpark
    
#     Предлагаю такое решение:

#     Например есть таблицы

# ---------------------------------------------
#     таблица продуктов
#     products:
#     product_id  |   product_name

#     1           |   prod_1
#     2           |   prod_2
#     3           |   prod_3
#     4           |   prod_4
#     5           |   prod_5

# ---------------------------------------------
#     таблица категорий
#     categories:
#     category_id     |   category_name

#     1               |   cat_1
#     2               |   cat_2
#     3               |   cat_3
#     4               |   cat_4

# ---------------------------------------------
#     таблица связей
#     connection:
#     product_id  |   category_id

#     1           |   1
#     1           |   2
#     2           |   1
#     3           |   3

# ---------------------------------------------
#     нужно сделать запрос:
#         соединить таблицу с продутами с таблицей со связями
#         соеденить результат с категориями
#         вывести только названия продуктов и категорий

#     На SQL я бы так делал:

#     SELECT p.product_name cat.category_name FROM products p
#     LEFT JOIN connection con ON p.product_id = con.product_id
#     LEFT JOIN categories cat ON con.category_id = cat.category_id
#     ORDER BY p.product_name, cat.category_name;


#     на сколько я понял в pySpark можно похожие на SQL запросы делать 
#     по этому с использованием pyspark это будет, наверное, так:

#     def get_pairs(products, categories, connection):
#         pairs = products.join(connection, "product_id").join(categories, "category_id").select("product_name", "category_name")
    
#         return pairs

#     (у меня pyspark так не заработал, поэтому не проверял)
        
#     По хорошему результат должен быть таким:

#      product_name | category_name 
    
#      prod_1       | cat_1
#      prod_1       | cat_2
#      prod_2       | cat_1
#      prod_3       | cat_3
#      prod_4       | NULL
#      prod_5       | NULL