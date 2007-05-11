/* ReadCommand.java
 *
 * Author: Luiz Carlos Irber Júnior
 * Criation date: 04-18-2007
 */

package trab1.btype.AST;

import java.util.*;

public class ReadCommand extends Command {

    public ReadCommand( Variable var ) {
        this.variable = var;
    }
    
    public void genC() {
        System.out.print("printf(\"What is the value of variable? \");\n");
        System.out.print("    scanf(\"%d\", &" + variable.value + ");\n");
    }
    
    private Variable variable;}
