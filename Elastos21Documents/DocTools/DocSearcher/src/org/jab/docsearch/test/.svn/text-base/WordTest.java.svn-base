/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the
 * Free Software Foundation, Inc.,
 * 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
 */
package org.jab.docsearch.test;

import java.io.IOException;

import org.apache.log4j.BasicConfigurator;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;

import org.jab.docsearch.converters.Word;

/**
 * Word test class
 *
 * @version $Id: WordTest.java,v 1.1 2006/06/15 16:08:00 henschel Exp $
  */
public class WordTest {
    /**
     * Logger
     */
    private static Logger logger = null; 

    /**
     * Main method
     *
     * @param args
     */
    public static void main(String[] args) {
        BasicConfigurator.configure();
        logger = Logger.getLogger(OpenDocumentTest.class);
        logger.setLevel(Level.DEBUG);

        int numArgs = args.length;
        if (numArgs != 1) {
            logger.debug("USAGE:\n\tjava WordTest word.doc");
            return;
        }

        String wordFile = args[0];
        
        WordTest wt = new WordTest();
        wt.test(wordFile);
    }

 
    /**
     * Test method
     *
     * @param wordFile
     */
    private void test(String wordFile) {
        logger.info("test('" + wordFile + "') entered");

        Word word = new Word(wordFile);

        // parse word file
        try {
            word.parse();
        }
        catch (IOException io) {
            logger.error("test() failed", io);
        }
    }
}
