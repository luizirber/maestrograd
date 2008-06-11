/* Variable.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */
 
package AST;

import java.util.*;

public class Variable extends Value {

    public Variable( char var ) {
        this.value = var;
    }
    
    public void genC() {
        System.out.print(value);
    }
}
