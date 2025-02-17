-- 1. find_customer
CREATE OR REPLACE PROCEDURE find_customer (
    customer_id IN NUMBER,
    found OUT NUMBER
) AS
BEGIN
    SELECT 1 INTO found
    FROM customers
    WHERE customer_id = find_customer.customer_id;
EXCEPTION
    WHEN NO_DATA_FOUND THEN
        found := 0;
    WHEN TOO_MANY_ROWS THEN
        found := 0;
        DBMS_OUTPUT.PUT_LINE('Multiple customers found with the same ID');
    WHEN OTHERS THEN
        found := 0;
        DBMS_OUTPUT.PUT_LINE('An unexpected error occurred: ' || SQLERRM);
END;
/

--2. find_product
CREATE OR REPLACE PROCEDURE find_product (
    productId IN NUMBER,
    price OUT products.list_price%TYPE,
    productName OUT products.product_name%TYPE
) AS
    categoryId products.category_id%TYPE;
BEGIN
    SELECT product_name, list_price, category_id INTO productName, price, categoryId
    FROM products
    WHERE product_id = find_product.productId;

    IF TO_CHAR(SYSDATE, 'MM') IN ('07', '08') AND categoryId IN (2, 5) THEN
        price := price * 0.85;
    END IF;

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        productName := NULL;
        price := 0;
    WHEN TOO_MANY_ROWS THEN
        productName := NULL;
        price := 0;
        DBMS_OUTPUT.PUT_LINE('Multiple products found with the same ID');
    WHEN OTHERS THEN
        productName := NULL;
        price := 0;
        DBMS_OUTPUT.PUT_LINE('An unexpected error occurred: ' || SQLERRM);
END;
/

-- 3. add_order
CREATE OR REPLACE PROCEDURE add_order (
    customer_id IN NUMBER,
    new_order_id OUT NUMBER
) AS
BEGIN
    new_order_id := generate_order_id();

    INSERT INTO orders (order_id, customer_id, status, salesman_id, order_date)
    VALUES (new_order_id, add_order.customer_id, 'Pending', 62, SYSDATE);

    COMMIT;
END;
/

-- 4. generate_order_id ()
CREATE OR REPLACE FUNCTION generate_order_id RETURN NUMBER IS
    max_order_id NUMBER;
BEGIN
    SELECT NVL(MAX(order_id), 0) + 1 INTO max_order_id
    FROM orders;
    RETURN max_order_id;
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An unexpected error occurred: ' || SQLERRM);
        RETURN NULL;
END;
/

-- 5. add_order_item
CREATE OR REPLACE PROCEDURE add_order_item (
    orderID IN order_items.order_id%TYPE,
    itemID IN order_items.item_id%TYPE,
    productID IN order_items.product_id%TYPE,
    quantity IN order_items.quantity%TYPE,
    price IN order_items.unit_price%TYPE
) AS
BEGIN
    INSERT INTO order_items (order_id, item_id, product_id, quantity, unit_price)
    VALUES (orderID, itemID, productID, quantity, price);

    COMMIT;
EXCEPTION
    WHEN OTHERS THEN
        DBMS_OUTPUT.PUT_LINE('An unexpected error occurred: ' || SQLERRM);
        ROLLBACK;
END;
/

-- 6. customer_order
CREATE OR REPLACE PROCEDURE customer_order (
    customerID IN NUMBER,
    orderID IN OUT NUMBER
) AS
    v_count NUMBER;
BEGIN
    SELECT COUNT(*)
    INTO v_count
    FROM orders
    WHERE customer_id = customerID AND order_id = orderID;

    IF v_count = 0 THEN
        orderID := 0; -- Order does not belong to customer
    END IF;
END;
/

-- 7. display_order_status
CREATE OR REPLACE PROCEDURE display_order_status (
    orderID IN NUMBER,
    status OUT orders.status%TYPE
) AS
BEGIN
    SELECT status INTO status
    FROM orders
    WHERE order_id = orderID;

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        status := NULL;
    WHEN OTHERS THEN
        status := NULL;
        DBMS_OUTPUT.PUT_LINE('An unexpected error occurred: ' || SQLERRM);
END;
/

-- 8. cancel_order
CREATE OR REPLACE PROCEDURE cancel_order (
    orderID IN NUMBER,
    cancelStatus OUT NUMBER
) AS
    orderStatus orders.status%TYPE;
BEGIN
    SELECT status INTO orderStatus
    FROM orders
    WHERE order_id = cancel_order.orderID;

    IF orderStatus = 'Canceled' THEN
        cancelStatus := 1;
    ELSIF orderStatus = 'Shipped' THEN
        cancelStatus := 2;
    ELSE
        UPDATE orders
        SET status = 'Canceled'
        WHERE order_id = cancel_order.orderID;
        cancelStatus := 3;
    END IF;

EXCEPTION
    WHEN NO_DATA_FOUND THEN
        cancelStatus := 0;
    WHEN OTHERS THEN
        cancelStatus := 0;
        DBMS_OUTPUT.PUT_LINE('An unexpected error occurred: ' || SQLERRM);
END;
/
