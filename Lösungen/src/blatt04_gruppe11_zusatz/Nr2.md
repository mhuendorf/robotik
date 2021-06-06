# Aufgabe 4.2

### Teil A

> Geben Sie die Matrizen A, B und H für den Kalman-Filter für die beschriebene Domäne an!

<!-- Analog zur VL -->

**Zustandsraum, Aktionsraum und Messraum:**

$$
\begin{aligned}
x:=\left(\begin{matrix}
x \\
z \\
\theta \\
\lambda \\
\beta 
\end{matrix}\right),~~

u:=\left(\begin{matrix}
\Delta x \\
\Delta z \\
\Delta \theta 
\end{matrix}\right),~~

Z:=\left(\begin{matrix}
x \\
z \\
\theta \\
\lambda
\end{matrix}\right)
\end{aligned}
$$

**Transitionsmodell, Aktionsmodell und Sensormodell:**

$$
\begin{aligned}
A:=I_5,~~

B:=\left(\begin{matrix}
1&0&0 \\
0&1&0 \\
0&0&1 \\
0&0&0 \\
\end{matrix}\right),~~

H:=\left(\begin{matrix}
1&0&0&0&0 \\
0&1&0&0&0 \\
0&0&1&0&0 \\
0&0&0&1&0 
\end{matrix}\right)
\end{aligned}
$$

### Teil B

> Modellieren Sie die Aktionen rot und tra:
> 
> - rot rotiert um den vorgegebenen Wert bei einer Standardabweichung von 0.02 und lässt x, z unverändert.
> - tra translatiert den Roboter um die vorgegebenen Werte bei einer Standardabweichung von 0.5 in beiden Dimensionen. Als Nebeneffekt ändert es möglicherweise die  Orientierung mit einer Standardabweichung von 0.01

**Rotation:**

$$
\begin{aligned}
P(x_{t+1}|u_t,x_t)&=n\cdot \left( Ax_t + Bf(u_t), RT_u  \right) \\ \\

RT&:=\left(\begin{matrix}
0&0&0&0&0 \\
0&0&0&0&0 \\
0&0&0.02&0&0 \\
0&0&0&0.001&0 \\
0&0&0&0&0 
\end{matrix}\right) \\
\end{aligned}
$$

$$
f\colon\mathbb{R}^{3}\to\mathbb{R}^{3},~f{\begin{pmatrix}a\\b\\c\end{pmatrix}}={\begin{pmatrix}0\\0\\c\end{pmatrix}}
$$

**Translation:**

$$
\begin{aligned}
P(x_{t+1}|u_t,x_t)&=n\cdot \left( Ax_t + Bf(u_t), TR_u  \right) \\ \\

TR&:=\left(\begin{matrix}
0.5 & 0 & 0 & 0 & 0 \\
0 & 0.5 & 0 & 0 & 0 \\
0 & 0 & 0.01 & 0 & 0 \\
0 & 0 & 0 & 0.001 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{matrix}\right)
\end{aligned}
$$

$$
f\colon\mathbb{R}^{3}\to\mathbb{R}^{3},~f{\begin{pmatrix}a\\b\\c\end{pmatrix}}={\begin{pmatrix}a\\b\\0\end{pmatrix}}
$$

### Teil C

> Im Startzustand befinde sich der Roboter an $(0, 0, 0)$, der Luftdruck sei 1000 hPa, und die Anzahl der Bundesländer sei 16. Berechnen Sie den Zustand (mehrdimensionaler Mittelwert und Standardabweichung), der sich ergibt, wenn der Roboter erst um 0.3 rad rotiert und anschließend um 2 Einheiten x und 3 Einheiten z translatiert. Geben Sie für alle vorkommenden Zustände die a-priori-Werte für Mittelwert und Varianz sowie die entsprechenden Kalman-Gewinnmatrizen an.

#### Rotation

$$
x_0:=\begin{pmatrix}
0 \\
0 \\
0 \\
1000 \\
16 
\end{pmatrix}
$$

**Kovarianzmatrix:**

$$
\begin{aligned}
\Sigma_0&=I_5 \\

\Sigma_Z&=\begin{pmatrix}
\sigma_x^2 & 0 & 0 & 0 \\
0 & \sigma_z^2 & 0 & 0 \\
0 & 0 & \sigma_\theta^2 & 0  \\
0 & 0 & 0 & \sigma_\lambda^2 \\
\end{pmatrix}
\end{aligned}
$$

**A-priori:**

$$
\begin{aligned}
\overline{x}_{t+1}&=Ax_t+Bu \\
\overline{\Sigma}_{t+1}&=A\Sigma_t A^T+\Sigma_u
\end{aligned}
$$

$$
\begin{aligned}
\overline{x}_{1}&=Ax_0+B \begin{pmatrix}0\\0\\0.3\end{pmatrix} \\
&=A \begin{pmatrix}0\\0\\0\\1000\\16\end{pmatrix} + B \begin{pmatrix}0\\0\\0.3\end{pmatrix} \\
&=\begin{pmatrix}0\\0\\0\\1000\\16\end{pmatrix}+\begin{pmatrix}0\\0\\0.3\\0\\0\end{pmatrix} \\
&=\begin{pmatrix}0\\0\\0.3\\1000\\16\end{pmatrix}
\end{aligned}
$$

$$
\begin{aligned}
\overline{\Sigma}_{1}&=A\Sigma_0 A^T+\Sigma_{u_{RT}} \\
&=I_5+\begin{pmatrix}
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0 & 0 & 0 \\
0 & 0 & 0.02 & 0 & 0 \\
0 & 0 & 0 & 0.001 & 0 \\
0 & 0 & 0 & 0 & 0 
\end{pmatrix} \\
&=\begin{pmatrix}
1 & 0 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 \\
0 & 0 & 1.02 & 0 & 0 \\
0 & 0 & 0 & 1.001 & 0 \\
0 & 0 & 0 & 0 & 1 
\end{pmatrix}
\end{aligned}
$$

**Kalman-Gewinnmatrix:**

$$
\begin{aligned}
K_{t+1}&=\overline{\Sigma}_{t+1}H^T(H\overline{\Sigma}_{t+1}H^T+\Sigma_z)^{-1}
\end{aligned}
$$

$$
\begin{aligned}
K_{1}&=\overline{\Sigma}_{1}H^T(H\overline{\Sigma}_{1}H^T+\Sigma_z)^{-1} \\
&=\begin{pmatrix}
1 & 0 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 \\
0 & 0 & 1.02 & 0 & 0 \\
0 & 0 & 0 & 1.001 & 0 \\
0 & 0 & 0 & 0 & 1 
\end{pmatrix}\cdot H^T \cdot\left(\begin{pmatrix}
1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 \\
0 & 0 & 1.02 & 0 \\
0 & 0 & 0 & 1.001
\end{pmatrix}+ \begin{pmatrix}
\sigma_x^2 & 0 & 0 & 0 \\
0 & \sigma_z^2 & 0 & 0 \\
0 & 0 & \sigma_\theta^2 & 0  \\
0 & 0 & 0 & \sigma_\lambda^2 \\
\end{pmatrix}\right)^{-1} \\
&=\begin{pmatrix}
1 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 \\
0 & 0 & 1.02 & 0 \\
0 & 0 & 0 & 1.001  \\
0 & 0 & 0 & 0
\end{pmatrix}\cdot \begin{pmatrix}
\frac{1}{\sigma_x^2+1} & 0 & 0 & 0 \\
0 & \frac{1}{\sigma_z^2+1} & 0 & 0 \\
0 & 0 & \frac{1}{1.02+\sigma_\theta^2} & 0  \\
0 & 0 & 0 & \frac{1}{1.001+\sigma_\lambda^2} \\
\end{pmatrix} \\
&=\begin{pmatrix}
\frac{1}{\sigma_x^2+1} & 0 & 0 & 0  & 0 \\
0 & \frac{1}{\sigma_z^2+1} & 0 & 0 & 0 \\
0 & 0 & \frac{1.02}{1.02+\sigma_\theta^2} & 0 & 0 \\
0 & 0 & 0 & \frac{1.001}{1.001+\sigma_\lambda^2} & 0 \\
0 & 0 & 0 & 0 & 0
\end{pmatrix}
\end{aligned}
$$

**A-posteriori:**

Mittelwert:

$$
\begin{aligned}
x_{t+1}=\overline{x}_{t+1}+K_{t+1}(z-H\overline{x}_{t+1})
\end{aligned}
$$

$$
\begin{aligned}
x_{1}&=\overline{x}_{1}+K_{1}(z-H\overline{x}_{1}) \\
&=\begin{pmatrix}0\\0\\0.3\\1000\\16\end{pmatrix}+ K_1\cdot \left( \begin{pmatrix}x_1\\z_1\\\theta_1\\\lambda_1\end{pmatrix} - \begin{pmatrix}0\\0\\0.3\\1000\end{pmatrix} \right) \\ \\
&\text{Dimensionsfehler: 5x1, 5x5, 4x1}~(\to 5\text{x}1~\text{mit 0}) \\ \\
&=\begin{pmatrix}0\\0\\0.3\\1000\\16\end{pmatrix}+ \begin{pmatrix} \frac{x_1}{\sigma_x^2+1}  \\ \frac{z_1}{\sigma_z^2+1} \\ \frac{1.02\theta_1-0.306}{1.02+\sigma_\theta^2} \\ \frac{1.001\lambda_1-1001}{1.001+\sigma_\lambda^2} \\ 0 \end{pmatrix} \\
&=\begin{pmatrix} \frac{x_1}{\sigma_x^2+1}  \\ \frac{z_1}{\sigma_z^2+1} \\ \frac{1.02\theta_1-0.306}{1.02+\sigma_\theta^2}+0.3 \\ \frac{1.001\lambda_1-1001}{1.001+\sigma_\lambda^2}+1000 \\ 16 \end{pmatrix}
\end{aligned}
$$

Kovarianzmatrix:

$$
\begin{aligned}
\Sigma_{t+1}&=(1-K_{t+1}H)\overline{\Sigma}_{t+1}
\end{aligned}
$$

$$
\begin{aligned}
\Sigma_{1}&=(I_5-K_{1}H)\overline{\Sigma}_{1} \\ \\
&\text{Dimensionsfehler K und H }\to\text{ Nullzeile} \\ \\
&=\begin{pmatrix}
1-\frac{1}{\sigma_x^2+1} & 0 & 0 & 0  & 0 \\
0 & 1-\frac{1}{\sigma_z^2+1} & 0 & 0 & 0 \\
0 & 0 & 1-\frac{1.02}{1.02+\sigma_\theta^2} & 0 & 0 \\
0 & 0 & 0 & 1-\frac{1.001}{1.001+\sigma_\lambda^2} & 0 \\
0 & 0 & 0 & 0 & 1
\end{pmatrix}\cdot \\
&\begin{pmatrix}
1 & 0 & 0 & 0 & 0 \\
0 & 1 & 0 & 0 & 0 \\
0 & 0 & 1.02 & 0 & 0 \\
0 & 0 & 0 & 1.001 & 0 \\
0 & 0 & 0 & 0 & 1 
\end{pmatrix} \\
&=\begin{pmatrix}
\frac{\sigma_x^2}{\sigma_x^2+1} & 0 & 0 & 0  & 0 \\
0 & \frac{\sigma_z^2}{\sigma_z^2+1} & 0 & 0 & 0 \\
0 & 0 & \frac{1.02\sigma_\theta^2}{1.02+\sigma_\theta^2} & 0 & 0 \\
0 & 0 & 0 & \frac{1.001\sigma_\lambda^2}{1.001+\sigma_\lambda^2} & 0 \\
0 & 0 & 0 & 0 & 1
\end{pmatrix}
\end{aligned}
$$

#### Translation

TBD
