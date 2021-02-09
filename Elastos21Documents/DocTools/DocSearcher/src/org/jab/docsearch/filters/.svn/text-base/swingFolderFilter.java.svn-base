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
package org.jab.docsearch.filters;

import java.io.File;

import javax.swing.filechooser.FileFilter;

import org.jab.docsearch.utils.Messages;

/**
 * Class swingFolderFilter
 * 
 * @version $Id: swingFolderFilter.java,v 1.3 2005/12/06 21:24:11 henschel Exp $
 */
public class swingFolderFilter extends FileFilter {
    /**
     * Overwrite FileWriter.accept(File)
     */
    public boolean accept(File file) {
        return file.isDirectory();
    }


    /**
     * Overwrite FileWriter.getDescription()
     */
    public String getDescription() {
        return Messages.getString("DocSearch.directories");
    }
}
