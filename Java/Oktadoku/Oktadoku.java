import gdp.stdlib.StdIn;

class Oktadoku {
  public enum Variante { normal, mitDiagonalen };
  private Variante v;
  public char[][] feld = new char [8][8];
 

  public Oktadoku(Variante var)  {  
	  this.v=var;
  }
  public void read()             {  
	  for (int i = 0; i < feld.length; i++) {
		if (StdIn.isEmpty()) {
			System.out.println("Uengultige Eingabe");
			System.exit(0);
		}
		  String input= StdIn.readString();
		
		if (input.length()!=8) {
			System.out.println("Uengultige Eingabe");
			System.exit(0);
		}
		for (int j = 0; j < feld[0].length; j++) {
			feld[i][j]=input.charAt(j);
		}
	}
	  if (!StdIn.isEmpty()) {
		System.out.println("Uengultige Eingabe");
		System.exit(0);
	}
	  
	  
  }
  public void write()            {  
	 for (int i = 0; i < feld.length; i++) {
		for (int j = 0; j < feld[0].length; j++) {
			if (feld[i][j]=='.') {
				feld[i][j]=' ';
			}
		}
	}
	 if (v==Variante.normal) {
		System.out.println("Oktadoku");
	}else {
		System.out.println("Oktadoku mit Diagonalen");
	}
	  System.out.print("+-----+-----+-----+-----+ \n");
	  for (int i = 0; i < 4; i++) {
		System.out.print("| " + feld[i][0] + " " + feld[i][1] + " | " + feld[i][2] + " " + feld[i][3] + " | " + feld[i][4] + " " + feld[i][5] + " | " + feld[i][6] + " " + feld[i][7] + " | \n" );
	}
	  System.out.print("+-----+-----+-----+-----+ \n");
	  for (int i = 4; i < 8; i++) {
		System.out.print("| " + feld[i][0] + " " + feld[i][1] + " | " + feld[i][2] + " " + feld[i][3] + " | " + feld[i][4] + " " + feld[i][5] + " | " + feld[i][6] + " " + feld[i][7] + " | \n" );
	}
	  System.out.print("+-----+-----+-----+-----+ \n");
  }		
  
  public boolean check()         {
	for (int i = 0; i < feld.length; i++) {
		for (int j = 0; j < feld[0].length; j++) {
			if (feld[i][j]!=' '&& feld[i][j]!= '0') {
				boolean prufZeile=checkRow(feld, i, j, feld[i][j]);
				if (!prufZeile) {
					return false;
				}
				boolean prufSpalte=checkSpalte(feld, i, j, feld[i][j]);
				if (!prufSpalte) {
					return false;
				}
				boolean prufBox=checkBox(feld, i, j, feld[i][j]);
				if (!prufBox) {
					return false;
				}
				if (v== Variante.mitDiagonalen) {
					if (i==j) {
						boolean prufDiagonal=checkDiagonal(feld, i, j, feld[i][j]);
						if (!prufDiagonal) {
							return false;
						}
					}
					if (i==7-j) {
						boolean prufDiagonal=checkDiagonal2(feld, i, j, feld[i][j]);
						if (!prufDiagonal) {
							return false;
						}
					}
					
				}
				
			}
		}
	}
	  return true;
	
  
  
  }
  public void solve() 	         {  
	 for (int i = 0; i < feld.length; i++) {
		for (int j = 0; j < feld[0].length; j++) {
			if (feld[i][j]=='0') {
				feld[i][j]=' ';
			}
		}
	}
	  boolean solved= solveSudoku(feld);
	  if (solved) {
		write();
	}else {
		System.out.println("nicht loesbar :-(");
	}
  }
  
  public boolean checkRow (char [][] feld, int row, int col, char zeichen) {
	 boolean currentCheck= true;
	  for (int i = 0; i < feld[0].length; i++) {
		if (i==col) {
			continue;
		}
		if (feld[row][i]==zeichen) {
			currentCheck=false;
			break;
		}
	}
	  return currentCheck;
  }
  public boolean checkSpalte (char [][] feld, int row, int col, char zeichen) {
	  boolean currentCheck=true;
	  for (int i = 0; i < feld.length; i++) {
		if (i==row) {
			continue;
		}
		if (feld[i][col]==zeichen) {
			currentCheck=false;
			break;
		}
	}
	  return currentCheck;
  }
  
  public boolean checkBox (char [][] feld, int row, int col, char zeichen) {
	  boolean currentCheck=true;
	  int boxRowStart= row- row%4;
	  int boxColStart= col - col%2;
	  for (int i = boxRowStart; i < boxRowStart+4; i++) {
		for (int j = boxColStart; j < boxColStart+2; j++) {
			if (i==row&&j==col) {
				continue;
			}
			if (feld[i][j]==zeichen) {
				currentCheck=false;
				break;
			}
		}
	}
	  return currentCheck;
  }
  
  public boolean checkDiagonal (char [][] feld, int row, int col, char zeichen) {
	  boolean currentCheck=true;
	  for (int i = 0; i < feld.length; i++) {
		for (int j = 0; j < feld[0].length; j++) {
			if (i==row && j==col) {
				continue;
			}
			if (i!=j) {
				continue;
			}
			if (feld[i][j]==' ') {
				continue;
			}
			if (i==j) {
				if (feld[i][j]==zeichen) {
					currentCheck=false;
					break;
				}
			}
			
		}
	}
	  
		  
	
	  return currentCheck;
  }
  public boolean checkDiagonal2(char [][] feld, int row, int col, char zeichen) {
	  boolean currentCheck=true;
	  for (int i = 0; i < feld.length; i++) {
			for (int j = 0; j < feld[0].length; j++) {
				if (i==row && j==col) {
					continue;
				}
				if (i==7-j) {
					if (feld[i][j]==zeichen) {
						currentCheck=false;
						break;
					}
				}
				if (i!=j) {
					continue;
				}
				if (feld[i][j]==' ') {
					continue;
				}
				
				
			}
		}
	  return currentCheck;
  }
  public boolean solveSudoku(char [][] feld) {
	  int row=-1;
	  int col=-1;
	  boolean isNotEmpty= true;
	  for (int i = 0; i < feld.length; i++) {
		for (int j = 0; j < feld[0].length; j++) {
			if (feld[i][j]==' ') {
				row=i;
				col=j;
				isNotEmpty=false;
				break;
			}
		}
		if (!isNotEmpty) {
			break;
		}
	}
	  if (isNotEmpty) {
		return true;
	}
	  for (int i = 1; i <=8 ; i++) {
		char iConvert= convertInt(i);
		  if (v==Variante.normal) {
			if (checkNormal(feld, row, col, iConvert)) {
				feld[row][col]= iConvert;
				if (solveSudoku(feld)) {
					return true;
				}
				else {
					feld[row][col]= ' ';
				}
			}
		}else {
			if (checkMitDiagonal(feld, row, col, iConvert)) {
				feld[row][col]= iConvert;
				if (solveSudoku(feld)) {
					return true;
				}
				else {
					feld[row][col]= ' ';
				}
		}
		  
		}
	  }
	  return false;
	  
  }
  public boolean checkNormal (char [][] feld, int row, int col, char zeichen) {
	  if (checkRow(feld, row, col, zeichen)&&checkSpalte(feld, row, col, zeichen)& checkBox(feld, row, col, zeichen)) {
		return true;
	}else {
		return false;
	}
  }
  public boolean checkMitDiagonal(char [][] feld, int row, int col, char zeichen) {
	 if (row==col) {
		 if (checkRow(feld, row, col, zeichen)&&checkSpalte(feld, row, col, zeichen)& checkBox(feld, row, col, zeichen)&&checkDiagonal(feld, row, col, zeichen)) {
				return true;
			}else {
				return false;
			}
	}else if (row==7-col) {
		if (checkRow(feld, row, col, zeichen)&&checkSpalte(feld, row, col, zeichen)& checkBox(feld, row, col, zeichen)&&checkDiagonal2(feld, row, col, zeichen)) {
			return true;
		}else {
			return false;
		}
	}
	 else {
		if (checkRow(feld, row, col, zeichen)&&checkSpalte(feld, row, col, zeichen)& checkBox(feld, row, col, zeichen)) {
			return true;
		}else {
			return false;
		}
	}
  }
  public char convertInt(int num) {
	  switch (num) {
	case 1: 
		return '1';
	case 2: 
		return '2';
	case 3: 
		return '3';
	case 4: 
		return '4';
	case 5: 
		return '5';
	case 6: 
		return '6';
	case 7: 
		return '7';
	case 8: 
		return '8';
	
	default:
		throw new IllegalArgumentException("Unexpected value: " + num);
	}
  }
  
}


