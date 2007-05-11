/* Numb.java
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */

package trab1.btype.AST;

import java.util.*;

public class Numb extends Value {

    public Numb( char val ) {
        this.value = val;
    }
    
    public void genC() {
        System.out.print(value);
    }}
