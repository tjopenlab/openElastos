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
package org.jab.docsearch.utils;

/**
 * Class docTypeHandler
 * 
 * @version $Id: docTypeHandler.java,v 1.3 2005/10/09 18:03:07 henschel Exp $
 */
public final class docTypeHandler {
    private String extension;
    private String desc;
    private String app;

    private docTypeHandler() {
        // normal constructor not visible
    }

    
    public docTypeHandler(String extension, String desc, String app) {
        this.desc = desc;
        this.extension = extension.toLowerCase();
        this.app = app;
    }


    public boolean isCompat(String ext) {
        String com = ext.toLowerCase();
        return (com.equals(extension));
    }


    public String descName() {
        return extension + " (" + desc + ") " + Utils.getNameOnly(app);
    }


    public String getApp() {
        return app;
    }


    public String getExtension() {
        return extension;
    }


    public String getDesc() {
        return desc;
    }
}
