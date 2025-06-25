#include <iostream>
#include <iomanip>

using namespace std;

void showMainMenu();
void showCategoryMenu(int category);
double processCategoryChoice(int categoryChoice, int quantities[], int itemCodes[], int& itemCount);
void printOrderSummary(const int itemCodes[], const int quantities[], int itemCount, double totalPrice);

void showColdDishes();
void showSoups();
void showMainCourses();
void showDesserts();
void showDrinks();

double calcColdDishPrice(int dishNumber, int quantity);
double calcSoupPrice(int soupNumber, int quantity);
double calcMainCoursePrice(int courseNumber, int quantity);
double calcDessertPrice(int dessertNumber, int quantity);
double calcDrinkPrice(int drinkNumber, int quantity);

const char* getDishName(int category, int itemNumber);

const int MAX_ORDER_ITEMS = 100; 

int main() {
    setlocale(LC_ALL, "Russian");

    int userChoice;
    double orderTotal = 0.0;
    int orderItems[MAX_ORDER_ITEMS]; 
    int itemQuantities[MAX_ORDER_ITEMS]; 
    int itemsInOrder = 0; 

    cout << "Добро пожаловать в наш ресторан!\n";
    cout << "Пожалуйста, выбирайте блюда из меню:\n";

    do {
        showMainMenu();
        cin >> userChoice;

        if (userChoice >= 1 && userChoice <= 5) {
            
            orderTotal += processCategoryChoice(userChoice, itemQuantities, orderItems, itemsInOrder);
        }
        else if (userChoice == 0) {
            
            printOrderSummary(orderItems, itemQuantities, itemsInOrder, orderTotal);
        }
        else {
            cout << "Такого пункта нет в меню, попробуйте еще раз.\n";
        }
    } while (userChoice != 0);

    cout << "Ждем вас снова!\n";
    return 0;
}

void showMainMenu() {
    cout << "\nГлавное меню:\n";
    cout << "1. Холодные закуски\n";
    cout << "2. Супы\n";
    cout << "3. Основные блюда\n";
    cout << "4. Десерты\n";
    cout << "5. Напитки\n";
    cout << "0. Завершить заказ\n";
    cout << "Ваш выбор: ";
}

void showCategoryMenu(int category) {
    switch (category) {
    case 1: showColdDishes(); break;
    case 2: showSoups(); break;
    case 3: showMainCourses(); break;
    case 4: showDesserts(); break;
    case 5: showDrinks(); break;
    }
}

double processCategoryChoice(int categoryChoice, int quantities[], int itemCodes[], int& itemCount) {
    int chosenItem;
    int itemQuantity;
    double itemTotal = 0.0;

    showCategoryMenu(categoryChoice);
    cin >> chosenItem;

    if (chosenItem >= 1 && chosenItem <= 5) {
        cout << "Сколько порций? ";
        cin >> itemQuantity;

        if (itemCount < MAX_ORDER_ITEMS) {
            itemCodes[itemCount] = categoryChoice * 10 + chosenItem;
            quantities[itemCount] = itemQuantity;
            itemCount++;
        }
        else {
            cout << "Извините, в заказе слишком много позиций.\n";
            return 0.0;
        }

        switch (categoryChoice) {
        case 1: itemTotal = calcColdDishPrice(chosenItem, itemQuantity); break;
        case 2: itemTotal = calcSoupPrice(chosenItem, itemQuantity); break;
        case 3: itemTotal = calcMainCoursePrice(chosenItem, itemQuantity); break;
        case 4: itemTotal = calcDessertPrice(chosenItem, itemQuantity); break;
        case 5: itemTotal = calcDrinkPrice(chosenItem, itemQuantity); break;
        }

        cout << "Добавлено в заказ: " << getDishName(categoryChoice, chosenItem) << " (" << itemQuantity << " порц.)\n";
    }
    else if (chosenItem != 0) {
        cout << "Некорректный выбор блюда.\n";
    }

    return itemTotal;
}

void showColdDishes() {
    cout << "\nХолодные закуски:\n";
    cout << "1. Сельдь под шубой - 150 руб.\n";
    cout << "2. Салат Оливье - 180 руб.\n";
    cout << "3. Мясная нарезка - 250 руб.\n";
    cout << "4. Сырная тарелка - 300 руб.\n";
    cout << "5. Баклажанные рулетики - 120 руб.\n";
    cout << "Выберите закуску (1-5) или 0 для отмены: ";
}


void showSoups() {
    cout << "\nПервые блюда:\n";
    cout << "1. Борщ со сметаной - 200 руб.\n";
    cout << "2. Солянка сборная - 250 руб.\n";
    cout << "3. Куриный суп с лапшой - 180 руб.\n";
    cout << "4. Грибной крем-суп - 220 руб.\n";
    cout << "5. Щи из свежей капусты - 190 руб.\n";
    cout << "Выберите суп (1-5) или 0 для отмены: ";
}

void showMainCourses() {
    cout << "\nОсновные блюда:\n";
    cout << "1. Узбекский плов - 350 руб.\n";
    cout << "2. Бефстроганов с картофелем - 400 руб.\n";
    cout << "3. Котлета по-киевски - 300 руб.\n";
    cout << "4. Жареная картошка с грибами - 280 руб.\n";
    cout << "5. Курица терияки - 320 руб.\n";
    cout << "Выберите блюдо (1-5) или 0 для отмены: ";
}


void showDesserts() {
    cout << "\nДесерты:\n";
    cout << "1. Тирамису классический - 250 руб.\n";
    cout << "2. Чизкейк Нью-Йорк - 220 руб.\n";
    cout << "3. Мороженое пломбир - 150 руб.\n";
    cout << "4. Фруктовый салат - 180 руб.\n";
    cout << "5. Шоколадный торт - 280 руб.\n";
    cout << "Выберите десерт (1-5) или 0 для отмены: ";
}


void showDrinks() {
    cout << "\nНапитки:\n";
    cout << "1. Чай черный/зеленый - 80 руб.\n";
    cout << "2. Кофе американо/капучино - 120 руб.\n";
    cout << "3. Сок апельсиновый/яблочный - 100 руб.\n";
    cout << "4. Минеральная вода - 50 руб.\n";
    cout << "5. Домашний лимонад - 90 руб.\n";
    cout << "Выберите напиток (1-5) или 0 для отмены: ";
}


double calcColdDishPrice(int dishNumber, int quantity) {
    const int prices[] = { 150, 180, 250, 300, 120 };
    return prices[dishNumber - 1] * quantity;
}


double calcSoupPrice(int soupNumber, int quantity) {
    const int prices[] = { 200, 250, 180, 220, 190 };
    return prices[soupNumber - 1] * quantity;
}


double calcMainCoursePrice(int courseNumber, int quantity) {
    const int prices[] = { 350, 400, 300, 280, 320 };
    return prices[courseNumber - 1] * quantity;
}


double calcDessertPrice(int dessertNumber, int quantity) {
    const int prices[] = { 250, 220, 150, 180, 280 };
    return prices[dessertNumber - 1] * quantity;
}


double calcDrinkPrice(int drinkNumber, int quantity) {
    const int prices[] = { 80, 120, 100, 50, 90 };
    return prices[drinkNumber - 1] * quantity;
}


const char* getDishName(int category, int itemNumber) {
    if (category == 1) {
        switch (itemNumber) {
        case 1: return "Сельдь под шубой";
        case 2: return "Салат Оливье";
        case 3: return "Мясная нарезка";
        case 4: return "Сырная тарелка";
        case 5: return "Баклажанные рулетики";
        }
    }
    else if (category == 2) {
        switch (itemNumber) {
        case 1: return "Борщ со сметаной";
        case 2: return "Солянка сборная";
        case 3: return "Куриный суп с лапшой";
        case 4: return "Грибной крем-суп";
        case 5: return "Щи из свежей капусты";
        }
    }
    else if (category == 3) {
        switch (itemNumber) {
        case 1: return "Узбекский плов";
        case 2: return "Бефстроганов с картофелем";
        case 3: return "Котлета по-киевски";
        case 4: return "Жареная картошка с грибами";
        case 5: return "Курица терияки";
        }
    }
    else if (category == 4) {
        switch (itemNumber) {
        case 1: return "Тирамису классический";
        case 2: return "Чизкейк Нью-Йорк";
        case 3: return "Мороженое пломбир";
        case 4: return "Фруктовый салат";
        case 5: return "Шоколадный торт";
        }
    }
    else if (category == 5) {
        switch (itemNumber) {
        case 1: return "Чай черный/зеленый";
        case 2: return "Кофе американо/капучино";
        case 3: return "Сок апельсиновый/яблочный";
        case 4: return "Минеральная вода";
        case 5: return "Домашний лимонад";
        }
    }

    return "Неизвестное блюдо";
}

void printOrderSummary(const int itemCodes[], const int quantities[], int itemCount, double totalPrice) {
    cout << "\n==============================================\n";
    cout << "              ВАШ ЗАКАЗ:\n";
    cout << "==============================================\n";

    for (int i = 0; i < itemCount; i++) {
        int category = itemCodes[i] / 10;
        int itemNumber = itemCodes[i] % 10;
        double price = 0;

        switch (category) {
        case 1: price = calcColdDishPrice(itemNumber, 1); break;
        case 2: price = calcSoupPrice(itemNumber, 1); break;
        case 3: price = calcMainCoursePrice(itemNumber, 1); break;
        case 4: price = calcDessertPrice(itemNumber, 1); break;
        case 5: price = calcDrinkPrice(itemNumber, 1); break;
        }

        cout << i + 1 << ". " << getDishName(category, itemNumber) << " - ";
        cout << quantities[i] << " x " << price << " руб. = ";
        cout << quantities[i] * price << " руб.\n";
    }

    cout << "==============================================\n";
    cout << "ИТОГО: " << totalPrice << " руб.\n";
    cout << "==============================================\n";
    cout << "Спасибо за ваш заказ! Приятного аппетита!\n";
}