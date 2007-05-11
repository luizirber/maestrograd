/*
 * ParseException.java
 *
 * Based on code form ParseException.java from Alexandre Harano e 
 * Mário Clemêncio Júnior.
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */
package trab1;

public class ParseException extends java.lang.Exception {
    
    public ParseException() {
    }
    
    public ParseException(String msg, char []input, int where) {

        if ( where == 0 ) 
          where = 1; 
        else 
          if ( where >= input.length )
            where = input.length;
        
        String strInput = new String( input, where - 1, input.length - where + 1 );
        String strError = msg + ": Error at " + where + ":" + strInput;
        System.out.print( "\n" + strError );
        System.exit(1);
    }
}
