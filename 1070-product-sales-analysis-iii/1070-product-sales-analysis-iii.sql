# Write your MySQL query statement below
SELECT
    product_id,
    first_year,
    quantity,
    price
FROM (
    SELECT
        product_id,
        year AS first_year,
        quantity,
        price,
        RANK() OVER (
            PARTITION BY product_id
            ORDER BY year
        ) AS rnk
    FROM Sales
) AS temp
WHERE rnk = 1;