package com.twoblock.blockdesigner.command;

import org.eclipse.core.commands.AbstractHandler;
import org.eclipse.core.commands.ExecutionEvent;
import org.eclipse.core.commands.ExecutionException;
import org.eclipse.ui.handlers.HandlerUtil;
 
public class Handler_Exit extends AbstractHandler {
 
   @Override
   public Object execute(ExecutionEvent event) throws ExecutionException {
      HandlerUtil.getActiveWorkbenchWindow(event).close();
      return null;
   }
 
}