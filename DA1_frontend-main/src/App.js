import { useEffect } from "react";
import Home from "./pages/home";
import Login from "./pages/login";
import Register from "./pages/register";
import { createBrowserRouter, RouterProvider } from "react-router-dom";
import { socket } from "./socket";
import { createContext } from "react";
import { AddDevice } from "./pages/addDevice";

export const myFetch = async (path, { body, method } = {}) => {
    let options = {
        method: method || "POST",
        headers: {
            "Content-Type": "application/json",
        },
        body: JSON.stringify(body)
    }

    return fetch(`${path}`, options)
	.then((res) => res.json());
};

export const AppContext = createContext(null);

export function App() {
    
    useEffect(() => {
        console.log("NODE_ENV", process.env.NODE_ENV)

        function onConnect() {
            console.log("socket connected");
        }

        function onDisconnect() {
            console.log("socket disconnected");
        }

        socket.on("connect", onConnect);
        socket.on("disconnect", onDisconnect);

        return () => {
            socket.off("connect");
            socket.off("disconnect");
        };
    }, []);

    const router = createBrowserRouter([
        {
            path: "/",
            element: <Home/>,
        },
        {
            path: "/add",
            element: <AddDevice />,
        },
        {
            path: "/login",
            element: <Login/>,
        },
        {
            path: "/register",
            element: <Register/>,
        },
    ]);

    return (
        <div>
            <AppContext.Provider value={{ socket }}>
                <RouterProvider router={router} />
            </AppContext.Provider>
        </div>
    );
}