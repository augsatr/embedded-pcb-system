import { mandiPrices } from "@/lib/mockData";
export default function Markets(){
  return (
    <div className="space-y-4">
      <h1 className="text-xl font-bold">Mandi Price Intelligence</h1>
      <p className="text-sm text-gray-500">Aggregated from Agmarknet, eNAM, and buyer bids. Filter by commodity, distance, and quality.</p>
      <div className="flex gap-2 text-sm">
        <select className="border rounded px-2 py-1"><option>All Commodities</option><option>Onion</option><option>Soybean</option><option>Tomato</option></select>
        <select className="border rounded px-2 py-1"><option>Within 50km (Pune)</option><option>Within 100km</option><option>Maharashtra</option></select>
        <span className="ml-auto text-xs bg-green-50 border px-2 py-1 rounded">🔄 Auto-refresh: 15 min • Last: 11:42 AM</span>
      </div>
      <div className="bg-white rounded-xl border overflow-x-auto">
        <table className="w-full text-sm">
          <thead className="bg-gray-50 text-xs"><tr><th className="p-3 text-left">Market / District</th><th>Commodity (Variety)</th><th>Modal</th><th>Min-Max</th><th>Arrivals</th><th>Transport</th><th>Action</th></tr></thead>
          <tbody>{mandiPrices.map(m=>(
            <tr key={m.market} className="border-t">
              <td className="p-3"><div className="font-medium">{m.market}</div><div className="text-xs text-gray-500">{m.district} • {m.distanceKm} km</div></td>
              <td className="text-center">{m.commodity}<div className="text-xs text-gray-500">{m.variety}</div></td>
              <td className="text-center font-bold">₹{m.modalPrice} {m.trend==="up"?<span className="text-green-600 text-xs">▲</span>:m.trend==="down"?<span className="text-red-600 text-xs">▼</span>:"—"}</td>
              <td className="text-center text-xs">₹{m.minPrice} - ₹{m.maxPrice}</td>
              <td className="text-center">{m.arrivalQty} q</td>
              <td className="text-center text-xs">₹85/q<br/><span className="text-gray-400">Truck 10MT</span></td>
              <td className="text-center"><button className="text-xs bg-krishi-600 text-white px-2 py-1 rounded">Get Offer</button></td>
            </tr>
          ))}</tbody>
        </table>
      </div>
      <div className="text-xs text-gray-500 p-3 bg-blue-50 rounded border">💡 <b>Price Discovery Logic:</b> Weighted modal across mandis + buyer bid overlay + arrival pressure index + logistics cost adjustment for net realisation at farm-gate.</div>
    </div>
  );
}
