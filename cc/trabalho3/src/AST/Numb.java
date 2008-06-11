/* Numb.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */

package AST;

import java.util.*;

public class Numb extends Value {

    public Numb( char val ) {
        this.value = val;
    }
    
    public void genC() {
        System.out.print(value);
    }
}
