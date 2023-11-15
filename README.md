# JVMA_C

---

## Short info

This is the implementation of [JVMA](https://github.com/stacksm4sher/JVMA) but writing in pure C.
Main difference between these two projects is that it is actually a class decompiler and compiler.

## More technical info

**JVMA** is **Java Virtual Machine Assembly**. Which means there should be an assembly language to assemble classes.
That implementation will provide such functionality.

**For example:**

We have some java code:

```java
package com.stacksm4sher.autokick;

import com.google.inject.Inject;
import com.stacksm4sher.autokick.commands.SetKickCommandSingleton;
import com.stacksm4sher.autokick.config.HibernateConfig;
import com.stacksm4sher.autokick.events.ConnectEventHandler;
import org.slf4j.Logger;
import org.spongepowered.api.Sponge;
import org.spongepowered.api.event.Listener;
import org.spongepowered.api.event.game.state.GameStartedServerEvent;
import org.spongepowered.api.event.network.ClientConnectionEvent.Join;
import org.spongepowered.api.plugin.Dependency;
import org.spongepowered.api.plugin.Plugin;

@Plugin(
        id = "autokick",
        name = "AutoKick",
        description = "auto kicks player if it was added to map",
        authors = {
                "stacksm4sher"
        },
        dependencies = {
                @Dependency(id = "hibernate-core", version = "5.2.2.Final"),
                @Dependency(id = "mysql-connector-java", version = "8.0.32")
        }
)
public class AutoKick {

    private final ConnectEventHandler connectEventHandler;
    private final SetKickCommandSingleton setKickCommandSingleton;
    private final Logger logger;

    @Inject
    public AutoKick(ConnectEventHandler connectEventHandler, SetKickCommandSingleton setKickCommandSingleton, Logger logger) {
        this.connectEventHandler = connectEventHandler;
        this.setKickCommandSingleton = setKickCommandSingleton;
        this.logger = logger;
    }

    @Listener
    public void onServerStart(GameStartedServerEvent event) {


        logger.info("Injecting auto kick plugin");
    
    ... and go on
}
```

We also have bytecode of the class, but It's not really readable:

```bin
CA FE BA BE 00 00 00 34 00 70 0A 00 15 00 3C 09
00 14 00 3D 09 00 14 00 3E 09 00 14 00 3F 08 00
40 0B 00 41 00 42 0A 00 43 00 44 0A 00 45 00 46
07 00 47 08 00 48 0B 00 49 00 4A 08 00 4B 0A 00
43 00 4C 07 00 4E 0B 00 51 00 52 08 00 53 08 00
54 0A 00 55 00 56 08 00 57 07 00 58 07 00 59 01
00 13 63 6F 6E 6E 65 63 74 45 76 65 6E 74 48 61
6E 64 6C 65 72 01 00 38 4C 63 6F 6D 2F 74 61 63
68 79 63 61 72 64 69 61 7A 78 63 2F 61 75 74 6F
6B 69 63 6B 2F 65 76 65 6E 74 73 2F 43 6F 6E 6E
... and go on
```

And here is an example of assembly language:

```JVMA
.gi:
    mnv 0
    mjv 52
    cpc 112
    af public
    tc var20
    sc var21
    ic 0
    fc 3
    mc 2
    ac 3

.cpi:
    var20 var88
    var21 var89
    var22 "connectEventHandler"
    var23 "Lcom/stacksm4sher/autokick/events/ConnectEventHandler;";
    var24 "setKickCommandSingleton"
    var25 "Lcom/stacksm4sher/autokick/commands/SetKickCommandSingleton;";
    var26 "logger"
    var27 "Lorg/slf4j/Logger;";
    var88 "com/stacksm4sher/autokick/AutoKick"
    var89 "java/lang/Object"

.ii:

.fi:
   private final var22 var23
   private final var24 var25
   private final var26 var27

   ; user created field
   private static final "staticLogger" "Lorg/slf4j/Logger"

.mi:
    public var28 var29 .c0
    public var37 var38 .c1

    ; user created method
    private "example" "(Ljava/lang/String;II)V" .exampleCode

.c0:
    aload 0
    invokespecial var1
    aload 0
    aload 1
    putfield var2
    aload 0
    aload 2
    putfield var3
    aload 0
    aload 3
    putfield var4
    return

.c1:
    aload 0
    getfield var4
    ldc var5
    invokeinterface var6
    invokestatic var7
    aload 0
    aload 0
    getfield var3
    invokevirtual var8
    iconst_1
    anewarray var9
    dup
    iconst_0
    ldc var10
    aastore
    invokeinterface var11
    pop
    aload 0
    getfield var4
    ldc var12
    invokeinterface var6
    invokestatic var13
    aload 0
    ldc var14
    aload 0
    getfield var4
    ldc var16
    invokeinterface var6
    aload 0
    getfield var4
    ldc var17
    invokeinterface var6
    invokestatic var18
    pop
    aload 0
    getfield var4
    ldc var19
    invokeinterface var6
    return

.exampleCode:
    getstatic Ljava/lang/System out Ljava/io/PrintStream;
    aload 1
    invokevirtual java/io/PrintStream println (Ljava/lang/String;)V

    getstatic Ljava/lang/System out Ljava/io/PrintStream;
    iload 2
    iload 3
    iadd
    invokevirtual java/io/PrintStream println (I)V

    return
```

As you may see JVM assembly code has almost the same structure as regular Assembly lang files.
I hope that it's our advantage and people who already worked with assembly lang will understand that language way faster!

## The main goal:

The main goal is to provide user an ability to change bytecode in compiled projects/runtime much easier and clear way.
IMHO current bytecode manipulation libraries are not good enough. 
They are not clear enough (such as default Reflection API, bytebuddy or CGLIB). 
Or not so optimized and user-friendly (such as objectweb ASM).

When you are looking for the first time at this JVM Assembly code you can not say that it is way easier than others.
But if you are trying to manipulate with bytecode you are probably know what you are doing, 
and you also know opcode semantic from JVM specification, so this language will help you use your knowledge properly.

Current goal is to reach MVP. Where you can compile/decompile classes, modify bytecode and run them again.
The second main goal is to create out of it java library to compile/decompile and modifying classes at runtime.

More info coming soon!
