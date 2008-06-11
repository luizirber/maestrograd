/* DecCommand.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */

package AST;

import java.util.*;

public class DecCommand extends Command {

    public DecCommand( Character var ) {
        this.variable = var;
    }
    
    public void genC() {
        System.out.print( variable + "--;\n" );
    }
    
    private Character variable;
}
