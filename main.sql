1. Retrieve names of students enrolled in any society.

SELECT DISTINCT s.StudentName
FROM STUDENT s
JOIN ENROLLMENT e ON s.RollNo = e.RollNo;

2. Retrieve all society names.

SELECT SocName
FROM SOCIETY;

3. Retrieve students' names starting with letter ‘A’.

SELECT StudentName
FROM STUDENT
WHERE StudentName LIKE 'A%';

4. Retrieve students' details studying in courses ‘computer science’ or ‘chemistry’.

SELECT *
FROM STUDENT
WHERE Course IN ('Computer Science', 'Chemistry');

5. Retrieve students’ names whose roll no either starts with ‘X’ or ‘Z’ and ends with ‘9’.

SELECT StudentName
FROM STUDENT
WHERE (RollNo LIKE 'X%' OR RollNo LIKE 'Z%') AND RollNo LIKE '%9';

6. Find society details with more than N TotalSeats where N is to be input by the user.

-- Assuming N is 25
SET @N = 25;

SELECT *
FROM SOCIETY
WHERE TotalSeats > @N;

7. Update society table for mentor name of a specific society.

-- Updating mentor name for society 'NSS'
UPDATE SOCIETY
SET MentorName = 'New Mentor'
WHERE SocName = 'NSS';

8. Find society names in which more than five students have enrolled.

SELECT s.SocName
FROM SOCIETY s
JOIN ENROLLMENT e ON s.SocID = e.SID
GROUP BY s.SocName
HAVING COUNT(*) > 5;

9. Find the name of the youngest student enrolled in society ‘NSS’.

SELECT s.StudentName
FROM STUDENT s
JOIN ENROLLMENT e ON s.RollNo = e.RollNo
JOIN SOCIETY soc ON e.SID = soc.SocID
WHERE soc.SocName = 'NSS'
ORDER BY s.DOB ASC
LIMIT 1;


10. Find the name of the most popular society (on the basis of enrolled students).

SELECT s.SocName
FROM SOCIETY s
JOIN ENROLLMENT e ON s.SocID = e.SID
GROUP BY s.SocName
ORDER BY COUNT(*) DESC
LIMIT 1;


11. Find the name of two least popular societies (on the basis of enrolled students).

SELECT s.SocName
FROM SOCIETY s
JOIN ENROLLMENT e ON s.SocID = e.SID
GROUP BY s.SocName
ORDER BY COUNT(*) ASC
LIMIT 2;


12. Find the student names who are not enrolled in any society.

SELECT StudentName
FROM STUDENT
WHERE RollNo NOT IN (SELECT RollNo FROM ENROLLMENT);



13. Find the student names enrolled in at least two societies.

SELECT s.StudentName
FROM STUDENT s
JOIN ENROLLMENT e ON s.RollNo = e.RollNo
GROUP BY s.StudentName
HAVING COUNT(*) >= 2;



14. Find society names in which maximum students are enrolled.

SELECT s.SocName
FROM SOCIETY s
JOIN ENROLLMENT e ON s.SocID = e.SID
GROUP BY s.SocName
HAVING COUNT(*) = (
    SELECT COUNT(*)
    FROM ENROLLMENT
    GROUP BY SID
    ORDER BY COUNT(*) DESC
    LIMIT 1
);


15. Find names of all students who have enrolled in any society and society names in which at least one student has enrolled.

-- Names of students who have enrolled in any society
SELECT DISTINCT s.StudentName
FROM STUDENT s
JOIN ENROLLMENT e ON s.RollNo = e.RollNo;

-- Society names in which at least one student has enrolled
SELECT DISTINCT soc.SocName
FROM SOCIETY soc
JOIN ENROLLMENT e ON soc.SocID = e.SID;


16. Find names of students who are enrolled in any of the three societies ‘Debating’, ‘Dancing’ and ‘Sashakt’.

SELECT DISTINCT s.StudentName
FROM STUDENT s
JOIN ENROLLMENT e ON s.RollNo = e.RollNo
JOIN SOCIETY soc ON e.SID = soc.SocID
WHERE soc.SocName IN ('Debating', 'Dancing', 'Sashakt');



17. Find society names such that its mentor has a name with ‘Gupta’ in it.

SELECT SocName
FROM SOCIETY
WHERE MentorName LIKE '%Gupta%';



18. Find the society names in which the number of enrolled students is only 10% of its capacity.

SELECT s.SocName
FROM SOCIETY s
JOIN (
    SELECT SID, COUNT(*) AS EnrolledCount
    FROM ENROLLMENT
    GROUP BY SID
) e ON s.SocID = e.SID
WHERE (e.EnrolledCount / s.TotalSeats) <= 0.1;




19. Display the vacant seats for each society.

SELECT s.SocName, (s.TotalSeats - IFNULL(e.EnrolledCount, 0)) AS VacantSeats
FROM SOCIETY s
LEFT JOIN (
    SELECT SID, COUNT(*) AS EnrolledCount
    FROM ENROLLMENT
    GROUP BY SID
) e ON s.SocID = e.SID;


20. Increment Total Seats of each society by 10%.

UPDATE SOCIETY
SET TotalSeats = TotalSeats * 1.1;


21. Add the enrollment fees paid (‘yes’/’No’) field in the enrollment table.

ALTER TABLE ENROLLMENT
ADD COLUMN FeesPaid ENUM('Yes', 'No') DEFAULT 'No';


22. Update date of enrollment of society id ‘s1’ to ‘2018-01-15’, ‘s2’ to current date and ‘s3’ to ‘2018-01-02’.

UPDATE ENROLLMENT
SET DateOfEnrollment = CASE
    WHEN SID = 's1' THEN '2018-01-15'
    WHEN SID = 's2' THEN CURDATE()
    WHEN SID = 's3' THEN '2018-01-02'
    ELSE DateOfEnrollment
END;


23. Create a view to keep track of society names with the total number of students enrolled in it.

CREATE VIEW SocietyEnrollmentCount AS
SELECT soc.SocName, COUNT(*) AS EnrollmentCount
FROM SOCIETY soc
JOIN ENROLLMENT e ON soc.SocID = e.SID
GROUP BY soc.SocName;


24. Find student names enrolled in all the societies.

SELECT s.StudentName
FROM STUDENT s
WHERE NOT EXISTS (
    SELECT SocID
    FROM SOCIETY
    WHERE NOT EXISTS (
        SELECT 1
        FROM ENROLLMENT
        WHERE ENROLLMENT.SID = SOCIETY.SocID
        AND ENROLLMENT.RollNo = s.RollNo
    )
);


25. Count the number of societies with more than 5 students enrolled in it.

SELECT COUNT(*)
FROM (
    SELECT SID, COUNT(*) AS EnrolledCount
    FROM ENROLLMENT
    GROUP BY SID
    HAVING EnrolledCount > 5
) AS Subquery;


26. Add column Mobile number in student table with default value ‘9999999999’.

ALTER TABLE STUDENT
ADD COLUMN Mobile VARCHAR(15) DEFAULT '9999999999';


27. Find the total number of students whose age is > 20 years.

SELECT COUNT(*)
FROM STUDENT
WHERE TIMESTAMPDIFF(YEAR, DOB, CURDATE()) > 20;


28. Find names of students who are born in 2001 and are enrolled in at least one society.

SELECT DISTINCT s.StudentName
FROM STUDENT s
JOIN ENROLLMENT e ON s.RollNo = e.RollNo
WHERE YEAR(s.DOB) = 2001;


29. Count all societies whose name starts with ‘S’ and ends with ‘t’ and at least 5 students are enrolled in the society.

SELECT COUNT(*)
FROM (
    SELECT SID
    FROM SOCIETY
    WHERE SocName LIKE 'S%t' AND SID IN (
        SELECT SID
        FROM ENROLLMENT
        GROUP BY SID
        HAVING COUNT(*) >= 5
    )
) AS Subquery;


30. Display the following information: Society name, Mentor name, Total Capacity, Total Enrolled, Unfilled Seats.

SELECT soc.SocName, soc.MentorName, soc.TotalSeats, IFNULL(e.EnrolledCount, 0) AS TotalEnrolled, (soc.TotalSeats - IFNULL(e.EnrolledCount, 0)) AS UnfilledSeats
FROM SOCIETY soc
LEFT JOIN (
    SELECT SID, COUNT(*) AS EnrolledCount
    FROM ENROLLMENT
    GROUP BY SID
) e ON soc.SocID = e.SID;

|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

Q2

1. Create User
To create a new user in MySQL:


CREATE USER 'username'@'localhost' IDENTIFIED BY 'password';


2. Create Role
MySQL does not have a native concept of roles like some other database systems, but you can mimic role behavior using privileges. However, you can create a role in PostgreSQL:

CREATE ROLE rolename;


3. Grant Privileges to a Role
To grant privileges to a role in PostgreSQL:


GRANT privilege1, privilege2, ... ON table_name TO role_name;




4. Revoke Privileges from a Role
To revoke privileges from a role in PostgreSQL:

REVOKE privilege1, privilege2, ... ON table_name FROM role_name;

REVOKE SELECT ON sales_data FROM sales_role;


5. Create Index
To create an index on a table in MySQL:


CREATE INDEX index_name ON table_name (column_name);

|||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

Q4


ER DIAGRAM TO RELATION DATABASE 




CREATE TABLE EMPLOYEE (
  Fname VARCHAR(255) NOT NULL,
  Minit CHAR(1) NOT NULL,
  Lname VARCHAR(255) NOT NULL,
  Bdate DATE NOT NULL,
  Ssn CHAR(11) NOT NULL PRIMARY KEY,
  Sex CHAR(1) NOT NULL,
  Salary DECIMAL(10,2) NOT NULL
);

CREATE TABLE DEPARTMENT (
  Name VARCHAR(255) NOT NULL PRIMARY KEY,
  Number_of_employees INT NOT NULL
);

CREATE TABLE LOCATIONS (
  Name VARCHAR(255) NOT NULL PRIMARY KEY,
  Number INT NOT NULL
);

CREATE TABLE WORKS_FOR (
  Ssn CHAR(11) NOT NULL,
  Name VARCHAR(255) NOT NULL,
  Start_date DATE NOT NULL,
  PRIMARY KEY (Ssn, Name, Start_date),
  FOREIGN KEY (Ssn) REFERENCES EMPLOYEE(Ssn),
  FOREIGN KEY (Name) REFERENCES DEPARTMENT(Name)
);

CREATE TABLE PROJECT (
  Name VARCHAR(255) NOT NULL PRIMARY KEY
);

CREATE TABLE SUPERVISION (
  Supervisor Ssn CHAR(11) NOT NULL,
  Supervisee Ssn CHAR(11) NOT NULL,
  PRIMARY KEY (Supervisor, Supervisee),
  FOREIGN KEY (Supervisor) REFERENCES EMPLOYEE(Ssn),
  FOREIGN KEY (Supervisee) REFERENCES EMPLOYEE(Ssn)
);

CREATE TABLE WORKS_ON (
  Ssn CHAR(11) NOT NULL,
  Name VARCHAR(255) NOT NULL,
  Hours INT NOT NULL,
  PRIMARY KEY (Ssn, Name),
  FOREIGN KEY (Ssn) REFERENCES EMPLOYEE(Ssn),
  FOREIGN KEY (Name) REFERENCES PROJECT(Name)
);

CREATE TABLE DEPENDENT (
  Name VARCHAR(255) NOT NULL,
  Sex CHAR(1) NOT NULL,
  Birth_date DATE NOT NULL,
  Relationship VARCHAR(255) NOT NULL,
  Ssn CHAR(11) NOT NULL,
  PRIMARY KEY (Ssn),
  FOREIGN KEY (Ssn) REFERENCES EMPLOYEE(Ssn)
);
