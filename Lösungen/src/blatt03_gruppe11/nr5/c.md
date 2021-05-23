# Nr. 5 c)
Die bisherigen Bagfiles enthalten vermutlich reelle Laserscans und sind daher leicht verrauscht gewesen. In der aktuellen Simulation wurden scheinbar noch keine Verrauschungen simuliert. Da erhaltenen Daten aus dem Laserscan sind daher so genau, wie es ein float zulässt.

Eine Situation in der ein Bagfile nicht mehr ausreicht ist, wenn, wie in Aufgabenteil d), auf die Umwelt reagiert werden und mit der Umwelt interagiert werden soll.
Ein paar konkrete Beispiele sind:
- wie in d) autonome Navigation
- Greifen, Verschieben oder Bewegen von Objekten
- testen von Ansteuerungen (Drehen Reifen durch (zu schnelle Beschleunigung)) etc.