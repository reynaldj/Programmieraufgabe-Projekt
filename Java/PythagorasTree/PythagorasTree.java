import gdp.stdlib.*;
/**
 * 
 */

/**
 * Zeichnen rekursiv Pythagoras Baum
 * @author James Reynaldi, Sven George, Elida Senguel
 * @version 0.0.0.1
 *  
 */

public class PythagorasTree {

	/**
	 * Wir setzen die Groesse des Quadrats 0.075 am Anfang.
	 * Wir setzen die x und y Koordinate am Anfang, sodass das erste Quadrat in der Mitte und ganz unten steht.
	 * Wir zeichnen auch den Rand des erste Quadrats am unten.
	 * @param args Anzahl von Rekursion
	
	 * 
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub
 int rekursionZahl= Integer.parseInt(args[0]);
  double xInitial=0.5;
  double yInitial=0.075;
  double size=0.075;
  StdDraw.line(xInitial-size, yInitial-size, xInitial+size, yInitial-size);
	draw(rekursionZahl, xInitial-size, yInitial-size, xInitial+size, yInitial-size, 0, 1);
	}
 
	
	/**
      den Dreieck zeichnen mit Hilfe des Pythagoras Theorem und auch sin cos Regeln
 * 
	 * @param x1 x Koordinate von der Ecke des Quadrats
	 * @param y1 y Koordinate von der Ecke des Quadrats
	 * @param x2 x Koordinate von der anderen Ecke des Quadrats
	 * @param y2 y Koordinate von der anderen Ecke des Quadrats
	 * @param xGradient x Verschiebung in der Gegenkathete/Ankathete
	 * @param yGradient y Verschiebung in der Gegenkathete/Ankathete
	 
	 * @return koordinateArray ein Array, der die Koordinate von der Ecke des Dreiecks speichert
	 */
	
	public static double [] drawTriangle(double x1, double y1, double x2, double y2,double xGradient, double yGradient) {
		double ankathetenAngle= (Math.random()*30 + 30)/180 * Math.PI ;
		double xLaenge= x2-x1;
		double yLaenge= y2-y1;
		double hypotenusLaenge= Math.sqrt(Math.pow(xLaenge, 2)+Math.pow(yLaenge, 2));
		double ankathetenLaenge= (Math.cos(ankathetenAngle))*hypotenusLaenge;
		double midLaenge= (Math.cos(ankathetenAngle))*ankathetenLaenge;
		double midVertLaenge= (Math.sin(ankathetenAngle))*ankathetenLaenge;
		double ratio= midLaenge/hypotenusLaenge;
		double xNeu= x2-ratio*xLaenge;
		double yNeu=y2-ratio*yLaenge;
		double gradientLaenge= Math.sqrt(Math.pow(xGradient, 2)+Math.pow(yGradient, 2));
		double ratioVert= midVertLaenge/gradientLaenge;
		double xNeu2=xNeu+ratioVert*xGradient;
		double yNeu2=yNeu+ratioVert*yGradient;
		double [] koordinateArray= {
			xNeu2,yNeu2
		};
//		StdDraw.line(x1, y1, xNeu2, yNeu2);
//		StdDraw.line(x2, y2, xNeu2, yNeu2);
//		StdDraw.line(x1, y1, x2, y2);
		
		return koordinateArray;
		
	}
	/**
	 * den Quadrat zeichnen mithilfe der Phythagoras Theorem
	 * @param x1 x Koordinate von der Ecke des Dreiecks (Basis von Quadrat)
	 * @param y1 y Koordinate von der Ecke des Dreiecks (Basis von Quadrat)
	 * @param x2 x Koordinate von der anderen Ecke des Dreiecks (Basis von Quadrat)
	 * @param y2 y Koordinate von der anderen Ecke des Dreiecks (Basis von Quadrat)
	 * @param xGradient x Verschiebung in der Gegenkathete/Ankathete von dem vorherigen Dreieck
	 * @param yGradient y Verschiebung in der Gegenkathete/Ankathete von dem vorherigen Dreieck
	 
	 * @return koordinateArrayDreieck ein Array, der die Koordinaten der neuen Ecke von dem Quadrat speichern, und x und y Verschiebung in der Gegenkathete/Ankathete
	 */
	
	public static double [] drawSquare(double x1, double y1, double x2, double y2, double xGradient, double yGradient) {
		double xLaenge= x2-x1;
		double yLaenge= y2-y1;
		double eckeLaenge= Math.sqrt(Math.pow(xLaenge, 2)+Math.pow(yLaenge, 2));
		double gradientLaenge= Math.sqrt(Math.pow(xGradient, 2)+Math.pow(yGradient, 2));
		double ratioLaenge= eckeLaenge/gradientLaenge;
		double xNeu1= x1 + ratioLaenge*xGradient;
		double yNeu1= y1 + ratioLaenge*yGradient;
		double xNeu2= x2 + ratioLaenge*xGradient;
		double yNeu2= y2+ ratioLaenge*yGradient;
		StdDraw.line(x1, y1, xNeu1, yNeu1);
		StdDraw.line(x2, y2, xNeu2, yNeu2);
		StdDraw.line(x1, y1, x2, y2);
		StdDraw.line(xNeu1, yNeu1, xNeu2, yNeu2);
		double [] koordinateArrayDreieck= {
				xNeu1,yNeu1,xNeu2,yNeu2,xGradient,yGradient
		};
		return koordinateArrayDreieck;
	}
	/**
	 * Rekursion Function, um ein Quadrat und ein Dreieck mit der Gegenkathete/Ankathete wieder zu zeichnen
	 * @param n Uebrige Anzahl von Rekursion
	 * @param x0 x Koordinate von der unteren Ecke des neuen Quadrats
	 * @param y0 y Koordinate von der unteren Ecke des neuen Quadrats
	 * @param x1 x Koordinate von der anderen unteren Ecke des neuen Quadrats
	 * @param y1 y Koordinate von der anderen unteren Ecke des neuen Quadrats
	 * @param xGradient x Verschiebung in der Gegenkathete/Ankathete
	 * @param yGradient y Verschiebung in der Gegenkathete/Ankathete
	 
	 * @return wenn Rekursions Anzahl erreicht, dann return nichtsF
	 */
	public static void draw (int n, double x0, double y0,double x1,double y1,double xGradient, double yGradient) {

		if (n==0) {
			return;
		}
		double [] koordinateArrayQuadrat=drawSquare(x0, y0, x1, y1, xGradient, yGradient);
		double [] koordinateArrayDreieck= drawTriangle(koordinateArrayQuadrat[0], koordinateArrayQuadrat[1], koordinateArrayQuadrat[2], koordinateArrayQuadrat[3], koordinateArrayQuadrat[4], koordinateArrayQuadrat[5]);
		draw(n-1,koordinateArrayDreieck[0], koordinateArrayDreieck[1], koordinateArrayQuadrat[2], koordinateArrayQuadrat[3], koordinateArrayDreieck[0]-koordinateArrayQuadrat[0], koordinateArrayDreieck[1]-koordinateArrayQuadrat[1]);
		draw(n-1, koordinateArrayQuadrat[0], koordinateArrayQuadrat[1], koordinateArrayDreieck[0], koordinateArrayDreieck[1], koordinateArrayDreieck[0]-koordinateArrayQuadrat[2], koordinateArrayDreieck[1]-koordinateArrayQuadrat[3]);
		
	}
	
	
}
