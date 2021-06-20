# Aufgabe 5.1

### Teil A

> Was sind die grundlegenden Unterschiede zwischen dem Kalman- und dem Erweiterten Kalman-Filter?

- Der Kalman-Filter ist linear (verwendet Matrizen).
- Der erweiterte Kalman-Filter verwendet eine Taylor-Approximation, um die Zustandsüberführung zu linearisieren, und partielle Ableitungen, um die Kovarianzmatrix zu linearisieren. Entsprechend kann der erweiterte Kalman-Filter für nicht lineare Vorgänge verwendet werden.

### Teil B

> Welche Rolle spielen die Jacobi-Matrizen im EKF?

Die Kovarianzmatrix wird mit den partiellen Ableitungen (Jacobi-Matrix) berechnet.

### Teil C

> Erklären Sie, mit welcher Situation der EKF nicht zurecht kommt.

- fehlerhafte initiale Position
- Linearisierung führt zu Fehlern, die durch ungenaue Positionsveränderungen verstärkt werden
- Die ermittelte Kovarianzmatrix kann geringer werden als die wahre Kovarianz

### Teil D

> Wann ist die Position der Berechnung im EKF genau bekannt?

Fragestellung ungenau gestellt, falls Bezug auf *genau*:

In einem (erweiterten) Kalman-Filter ist die Position des Roboters nie zu 100% Genauigkeit bestimmbar. Andernfalls ist die Position nach der Korrektur des Fehlers bekannt und kann für weitere Schritte verwendet werden.
