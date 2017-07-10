-- https://leetcode.com/problemset/database/
-- 175. Combine Two Tables
SELECT p.FirstName, p.LastName, a.City, a.State
FROM Person p
LEFT OUTER JOIN Address a ON a.PersonId = p.PersonId;


-- 176. Second Highest Salary
SELECT max(Salary) SecondHighestSalary FROM Employee
WHERE Salary < (SELECT max(Salary) FROM Employee);


-- 177. Nth Highest Salary


-- 178. Rank Scores
SELECT
  Score,
  @rank := @rank + (@last <> @last := Score) Rank
FROM Scores, (SELECT @rank := 0, @last := -1) init
ORDER BY Score DESC;


-- 180. Consecutive Numbers
SELECT DISTINCT num ConsecutiveNums FROM
  (SELECT
    num,
    @count := if(@last = @last := num, @count + 1, 1) n
  FROM Logs) t,
  (SELECT @count := 0, @last:=(SELECT num FROM Logs Limit 1)) init
WHERE t.n >= 3;


-- 181. Employees Earning More Than Their Managers
SELECT e1.Name Employee
FROM Employee e1
INNER JOIN Employee e2 ON e1.ManagerId = e2.Id
WHERE e1.Salary > e2.Salary;


-- 182. Duplicate Emails
SELECT Email
FROM Person
GROUP BY Email
HAVING COUNT(Email) > 1;


-- 183. Customers Who Never Order
-- I.
SELECT c.Name Customers
FROM Customers c
LEFT OUTER JOIN Orders o ON c.Id = o.CustomerId
WHERE o.Id IS NULL;
-- II.
SELECT Name Customers
FROM Customers
WHERE Id NOT IN (
  SELECT CustomerId
  FROM Orders
);


-- 184. Department Highest Salary
SELECT d.name Department, e.name Employee, e.Salary
FROM (SELECT DepartmentId, max(Salary) Salary FROM Employee GROUP BY DepartmentId) tmp
INNER JOIN Department d
ON tmp.DepartmentId = d.Id
INNER JOIN Employee e
ON tmp.DepartmentId = e.DepartmentId AND tmp.Salary = e.Salary;

-- 185. Department Top Three Salaries


-- 196. Delete Duplicate Emails
DELETE FROM Person
WHERE Id NOT IN (
  SELECT Id from (
    SELECT MIN(Id) Id
    FROM Person
    GROUP BY Email
  ) tmp
);


-- 197. Rising Temperature
SELECT w2.Id
FROM Weather w1
INNER JOIN Weather w2 ON w2.Date = SUBDATE(w1.Date, -1)
WHERE w1.Temperature < w2.Temperature;


-- 262. Trips and Users
