#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class Product {
public:
    std::string productID;
    std::string name;
    double price;

    Product(std::string id, std::string n, double p) : productID(id), name(n), price(p) {}
};

class ShoppingCart {
public:
    std::vector<std::pair<Product, int>> items;

    void addProduct(Product product, int quantity) {
        items.push_back(std::make_pair(product, quantity));
    }

    double calculateTotal() const {
        double total = 0;
        for (const auto& item : items) {
            total += item.first.price * item.second;
        }
        return total;
    }
};

class Order {
public:
    int orderID;
    ShoppingCart cart;

    Order(int id, ShoppingCart c) : orderID(id), cart(c) {}

    void displayOrder() const {
        std::cout << "Order ID: " << orderID << std::endl;
        std::cout << "Total Amount: " << cart.calculateTotal() << std::endl;
        std::cout << "Order Details:" << std::endl;
        std::cout << std::setw(10) << "Product ID" << std::setw(10) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Quantity" << std::endl;
        for (const auto& item : cart.items) {
            std::cout << std::setw(10) << item.first.productID << std::setw(10) << item.first.name << std::setw(10) << item.first.price << std::setw(10) << item.second << std::endl;
        }
    }
};

void displayProducts(const std::vector<Product>& products) {
    std::cout << std::setw(10) << "Product ID" << std::setw(10) << "Name" << std::setw(10) << "Price" << std::endl;
    for (const auto& product : products) {
        std::cout << std::setw(10) << product.productID << std::setw(10) << product.name << std::setw(10) << product.price << std::endl;
    }
}

void displayShoppingCart(const ShoppingCart& cart) {
    std::cout << std::setw(10) << "Product ID" << std::setw(10) << "Name" << std::setw(10) << "Price" << std::setw(10) << "Quantity" << std::endl;
    for (const auto& item : cart.items) {
        std::cout << std::setw(10) << item.first.productID << std::setw(10) << item.first.name << std::setw(10) << item.first.price << std::setw(10) << item.second << std::endl;
    }
}

int main() {
    std::vector<Product> products = {
        Product("ABC", "Paper", 20),
        Product("CDE", "Pencil", 10),
        Product("QWE", "Paper", 20),
        Product("TRE", "Pencil", 10),
        Product("ASD", "Paper", 20),
        Product("ZXC", "Pencil", 10)
    };

    ShoppingCart cart;
    std::vector<Order> orders;
    int orderCounter = 1;

    while (true) {
        std::cout << "Menu:\n1. View Products\n2. View Shopping Cart\n3. View Orders\n4. Exit\n";
        int choice;
        std::cin >> choice;

        if (choice == 1) {
            displayProducts(products);
            while (true) {
                std::cout << "Enter the ID of the product you want to add in the shopping cart: ";
                std::string id;
                std::cin >> id;
                bool found = false;
                for (const auto& product : products) {
                    if (product.productID == id) {
                        std::cout << "Enter quantity: ";
                        int quantity;
                        std::cin >> quantity;
                        cart.addProduct(product, quantity);
                        std::cout << "Product added successfully!\n";
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Product ID not found.\n";
                }
                std::cout << "Do you want to add another product? (Y/N): ";
                char addAnother;
                std::cin >> addAnother;
                if (addAnother != 'Y' && addAnother != 'y') {
                    break;
                }
            }
        } else if (choice == 2) {
            displayShoppingCart(cart);
            std::cout << "Do you want to check out all the products? (Y/N): ";
            char checkout;
            std::cin >> checkout;
            if (checkout == 'Y' || checkout == 'y') {
                orders.push_back(Order(orderCounter++, cart));
                std::cout << "You have successfully checked out the products!\n";
                cart = ShoppingCart(); // Clear the cart
            }
        } else if (choice == 3) {
            for (const auto& order : orders) {
                order.displayOrder();
                std::cout << std::endl;
            }
        } else if (choice == 4) {
            break;
        } else {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}