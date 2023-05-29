Тестовая задача 3. Язык С++, Среда разработки Qt, либо C#, Среда разработки не ниже Visual Studio 2019 и технологии GUI - либо WinForms, либо WPF - на Ваше усмотрение.
Задача. Написать оконное приложение под Windows, с БД, поддерживающей механизм нотификаций (change notification) на Ваш выбор. Приложение должно отображать данные из таблицы в БД, синхронизация данных с БД осуществляется через механизм notify.

Приложение содержит следующие элементы управления:
1. Таблица
2. Поля для ввода данных подключения к базе данных.
3. Кнопки старт и стоп.

База данных. Состоит из одной таблицы с колонками id (integer) , flag(boolean), data(text).

Работа приложения. Приложение содержит 2 потока: главный поток GUI и поток обмена с базой данных. По нажатию кнопки старт в потоке обмена с базой данных устанавливается подключение к БД и подписывается на notify.
Обработка уведомлений от базы данных и все запросы к бд происходят только в потоке обмена с базой данных.
По нажатию стоп соединение с бд закрывается.
Проверяемые сценарии работы:
1. Запустили приложение, нажали старт. В БД выполнили скрипт добавляющий 1000 строк в таблицу в одной транзакции. Добавление строк в таблице GUI должно произойти
по возможности без подвисаний и ощутимых задержек.
2. Запустили приложение, нажали старт. В БД в таблице уже есть 1000 строк со значеним flag = true. Выполняем update меняющий flag на значение false.
Обновление строк в таблице GUI должно произойти по возможности без подвисаний и ощутимых задержек.

Работа с БД (хранимые процедуры или просто sql запросы), организация notify от таблицы, расположение элементов GUI - на ваше усмотрение.
