/* PrintCommand.java
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */

package trab1.btype.AST;

import java.util.*;

public class PrintCommand extends Command {

    public PrintCommand( Value val ) {
        this.value = val;
    }
    
    public void genC() {
        System.out.print("printf(\"%d\\n\", " + value.value + ");\n");
    }
    
    private Value value;}
