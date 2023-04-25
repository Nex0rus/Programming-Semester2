# Currency rate monitoring telegram bot
This bot can asinchronously monitor the Central bank API with currency rate and retrieve the JSON data using CURL requests.
## Список команд
### - `/currencies`
отправляет запрос на сервер, получает данные о валютах в формате JSON и возвращает форматированный список в виде сообщения. В случае, если время между подобными запросами меньше времени обновления информации на сервере, то возвращаются кэшированные данные.
Пример:
![image](https://user-images.githubusercontent.com/90113365/234377427-dc52c096-8f92-4012-b863-59bfe4bc3659.png)

### - `/show` `Название валюты`
Взвращает более точную информацию по курсу валюты с заданным названием.
Пример:
![image](https://user-images.githubusercontent.com/90113365/234377544-706dd01e-cd7a-49c4-8839-ab0b1880af62.png)

### - `/get_file` `Имя файла`
Возвращает информацию о всех валютах в виде `.csv` файла с заданным названием (с разделителем по запятой)
Пример:
![image](https://user-images.githubusercontent.com/90113365/234378035-d8c1bad4-619a-4d39-b302-07b3673c469f.png)
![image](https://user-images.githubusercontent.com/90113365/234378589-15db7d26-5ab1-40c2-8ba3-874d2a44c069.png)
