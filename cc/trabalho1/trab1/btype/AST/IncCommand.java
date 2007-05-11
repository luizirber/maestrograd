/* IncCommand.java
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */

package trab1.btype.AST;

import java.util.*;

public class IncCommand extends Command {

    public IncCommand( Variable var ) {
        this.variable = var;
    }
    
    public void genC() {
        System.out.print( variable.value + "++;\n" );
    }
    
    private Variable variable;}
