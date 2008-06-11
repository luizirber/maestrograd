/* PrintCommand.java
 *
 * Author: Luiz Carlos Irber Junior
 * Criation date: 04-18-2007
 */

package AST;

import java.util.*;

public class PrintCommand extends Command {

    public PrintCommand( Value val ) {
        this.value = val;
    }
    
    public void genC() {
        System.out.print("printf(\"%d\\n\", " + value.value + ");\n");
    }
    
    private Value value;
}
