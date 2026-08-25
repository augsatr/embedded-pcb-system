export default function Logistics(){
  return (
    <div className="space-y-4">
      <h1 className="text-xl font-bold">Logistics & Storage Coordination</h1>
      <div className="grid md:grid-cols-2 gap-6">
        <div className="bg-white p-4 rounded-xl border">
          <h3 className="font-semibold text-sm">🚛 Transport Options (Junnar → Pune APMC, 12km)</h3>
          <div className="mt-3 space-y-2 text-sm">
            <div className="flex justify-between p-2 border rounded"><div><div className="font-medium">Shared Truck (FPO Pool)</div><div className="text-xs text-gray-500">10 MT • Pickup tomorrow 6 AM • Split cost</div></div><div className="text-right"><div className="font-bold">₹42/q</div><button className="text-xs bg-krishi-600 text-white px-2 py-1 rounded">Book</button></div></div>
            <div className="flex justify-between p-2 border rounded"><div><div className="font-medium">Dedicated Mini-Truck</div><div className="text-xs text-gray-500">5 MT • On-demand</div></div><div className="text-right"><div className="font-bold">₹85/q</div><button className="text-xs border px-2 py-1 rounded">Book</button></div></div>
            <div className="flex justify-between p-2 border rounded bg-green-50"><div><div className="font-medium">Buyer Pickup (Sahyadri Farms)</div><div className="text-xs text-gray-500">Free if ≥10 MT • Verified buyer</div></div><div className="text-right"><div className="font-bold text-green-700">FREE</div><button className="text-xs bg-green-600 text-white px-2 py-1 rounded">Accept</button></div></div>
          </div>
        </div>
        <div className="bg-white p-4 rounded-xl border">
          <h3 className="font-semibold text-sm">🏬 Storage Options (Nearby)</h3>
          <div className="mt-3 space-y-2 text-sm">
            <div className="p-2 border rounded flex justify-between"><div><div className="font-medium">NAFED Warehouse - Junnar</div><div className="text-xs text-gray-500">2 km • Cold + Dry • 500 MT cap • WDRA registered</div><div className="text-xs">₹45/q/week • Insurance included</div></div><div><button className="text-xs bg-krishi-600 text-white px-2 py-1 rounded">Reserve</button></div></div>
            <div className="p-2 border rounded flex justify-between opacity-60"><div><div className="font-medium">Private Godown - Narayangaon</div><div className="text-xs text-gray-500">8 km • Dry only • 100 MT</div><div className="text-xs">₹30/q/week</div></div><div><button className="text-xs border px-2 py-1 rounded">Reserve</button></div></div>
          </div>
          <div className="text-xs text-gray-500 mt-2">Holding 12 MT onion for 14 days = ₹7,560 storage vs +₹34,560 gain (forecast). Net +₹27k.</div>
        </div>
      </div>
      <div className="bg-white p-4 rounded-xl border">
        <h3 className="font-semibold text-sm">Bulk Aggregation Benefit</h3>
        <p className="text-xs text-gray-600 mt-1">Combine with Solapur cluster (40 MT) to fill 20 MT truck, reduce cost from ₹85/q to ₹42/q, and meet institutional buyer's 50 MT lot size. Platform auto-suggests pooling.</p>
      </div>
    </div>
  );
}
